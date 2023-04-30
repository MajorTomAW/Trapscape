#include "BPCharacterBase.h"

// Sets default values
ABPCharacterBase::ABPCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!HealthComponent)
	{
		HealthComponent = CreateDefaultSubobject<UACHealthComponent>("HealthComponent");
		HealthComponent->SetIsReplicated(true);
	}
}

// Called when the game starts or when spawned
void ABPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

