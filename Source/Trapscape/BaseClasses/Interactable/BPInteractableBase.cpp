// Fill out your copyright notice in the Description page of Project Settings.


#include "BPInteractableBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

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
	if(!InteractWidgetComponent)
	{
		InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Interact Widget");
		InteractWidgetComponent->SetupAttachment(InteractHitbox);
		InteractWidgetComponent->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void ABPInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	InteractWidget = Cast<UWInteract>(InteractWidgetComponent->GetWidget());
	InteractWidget->SetupInteractUI(InteractInfo.InteractingText, InteractInfo.ObjectName, InteractInfo.bUseProgress);
}



// Called every frame
void ABPInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABPInteractableBase::ShowInteractInterface_Implementation(bool bShow)
{
	if(bInteractable)
	{
		InteractWidgetComponent->SetVisibility(bShow);
	}
}

void ABPInteractableBase::SendIsPressed_Implementation(bool bIsPressed)
{
	if(bInteractable)
	{
		InteractWidget->SendIsPressed(bIsPressed);
	}
}

void ABPInteractableBase::InteractProgress_Implementation(float Progress)
{
	if(bInteractable)
	{
		InteractWidget->UpdateProgress(Progress);
	}
}

void ABPInteractableBase::Interact_Implementation(ABPPlayerBase* Player)
{
	if(bInteractable)
	{
		InteractWithObject(Player);
	}
}

bool ABPInteractableBase::GetUseProgress_Implementation()
{
	return InteractInfo.bUseProgress;
}

void ABPInteractableBase::InteractWithObject_Implementation(ABPPlayerBase* Player)
{

}

void ABPInteractableBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABPInteractableBase, bInteractable);
}
