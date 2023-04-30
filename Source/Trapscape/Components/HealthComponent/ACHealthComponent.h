#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateHealth, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateMaxHealth, float, NewMaxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAPSCAPE_API UACHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UACHealthComponent();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(Replicated)
		float CurrentHealth;
	UPROPERTY(Replicated)
		bool bIsDead = false;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	UFUNCTION()
		void OwnerDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser);

	//Values
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
		float PlayerHealth = 100.0f;
	
	//Dispatchers
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnPlayerDeath OnPlayerDeath;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnUpdateHealth OnUpdateHealth;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnUpdateMaxHealth OnUpdateMaxHealth;
	//Functions
	UFUNCTION(BlueprintCallable)
		void HealPlayer(float HealValue);
	UFUNCTION(BlueprintCallable)
		void ResetHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetCurrentHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetMaxHealth();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetIsDead();
};
