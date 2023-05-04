// Fill out your copyright notice in the Description page of Project Settings.


#include "BPInteractableBase.h"

// Sets default values
ABPInteractableBase::ABPInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if(!InteractHitbox)
	{
		InteractHitbox = CreateDefaultSubobject<UBoxComponent>("Interact Hitbox");
		InteractHitbox->SetCollisionObjectType(ECC_GameTraceChannel4);
		InteractHitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		InteractHitbox->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
	}
}

// Called when the game starts or when spawned
void ABPInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

