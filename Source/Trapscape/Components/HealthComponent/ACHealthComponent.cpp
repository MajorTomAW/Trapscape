#include "ACHealthComponent.h"

#include "Net/UnrealNetwork.h"

UACHealthComponent::UACHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UACHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UACHealthComponent::OwnerDamage);
	CurrentHealth = PlayerHealth;
}

void UACHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UACHealthComponent::OwnerDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser)
{
	if (!bIsDead)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, GetMaxHealth());
		OnUpdateHealth.Broadcast(CurrentHealth);
		if (CurrentHealth <= 0.0f)
		{
			bIsDead = true;
			OnPlayerDeath.Broadcast();
		}
	}
}

void UACHealthComponent::HealPlayer(float HealValue)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealValue, 0.0f, GetMaxHealth());
	if (bIsDead) bIsDead = false;
	OnUpdateHealth.Broadcast(CurrentHealth);
}

void UACHealthComponent::ResetHealth()
{
	CurrentHealth = PlayerHealth;
	bIsDead = false;
	OnUpdateHealth.Broadcast(CurrentHealth);
}

//Pure Function
float UACHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}
float UACHealthComponent::GetMaxHealth()
{
	return PlayerHealth;
}
bool UACHealthComponent::GetIsDead()
{
	return bIsDead;
}

//Replication
void UACHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UACHealthComponent, CurrentHealth);
	DOREPLIFETIME(UACHealthComponent, bIsDead);
}