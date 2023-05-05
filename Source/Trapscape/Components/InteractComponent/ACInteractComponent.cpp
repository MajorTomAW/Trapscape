// Fill out your copyright notice in the Description page of Project Settings.


#include "ACInteractComponent.h"

#include "CollisionDebugDrawingPublic.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Trapscape/Interfaces/Interacting/InteractInterface.h"
#include "Trapscape/BaseClasses/Character/Player/BPPlayerBase.h"

// Sets default values for this component's properties
UACInteractComponent::UACInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UACInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	ABPPlayerBase* PlayerRef = Cast<ABPPlayerBase>(GetOwner());
	PlayerCameraComponent = PlayerRef->ThirdPersonCam;
}


// Called every frame
void UACInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UACInteractComponent::StartScanning_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(InteractTimerHandle, this, &UACInteractComponent::ScanInteract, 0.2f, true);
}

void UACInteractComponent::ScanInteract()
{
	if(PlayerCameraComponent)
	{
		FHitResult HitResult;
		const FVector StartLocation = PlayerCameraComponent->GetComponentLocation();
		const FVector EndLocation = (PlayerCameraComponent->GetForwardVector() * ScanRange) + StartLocation;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());
		//DrawLineTraces(GetWorld(), StartLocation, EndLocation, TArray<FHitResult>(), 2.0f);
		if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel3, Params, FCollisionResponseParams()))
		{
			if(TargetActor != HitResult.GetActor())
			{
				//Scanned a new overlap
				NewOverlap(HitResult.GetActor());
			}
		}
		else
		{
			if(!bCurrentlyInteracting)
			{
				//End the Overlap
				EndOverlap();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact Component: Got bad Camera Component"));
	}
}

void UACInteractComponent::StopInteracting_Implementation()
{
}

void UACInteractComponent::StartInteracting_Implementation()
{
}

void UACInteractComponent::HandleTimer_Implementation(bool bPause)
{
	if(bPause)
	{
		GetWorld()->GetTimerManager().PauseTimer(InteractTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().UnPauseTimer(InteractTimerHandle);
	}
}

void UACInteractComponent::ShowInteractUI_Implementation(bool bShow, AActor* Actor)
{
	if(Actor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		IInteractInterface::Execute_ShowInteractInterface(Actor, bShow);
		UKismetSystemLibrary::PrintString(GetWorld(), "Show Interact Widget");
	}
}

void UACInteractComponent::EndOverlap_Implementation()
{
	if(TargetActor)
	{
		ShowInteractUI(false, TargetActor);
		TargetActor = nullptr;
	}
}

void UACInteractComponent::NewOverlap_Implementation(AActor* Actor)
{
	UKismetSystemLibrary::PrintString(GetWorld(), UKismetSystemLibrary::GetObjectName(Actor));
	if(TargetActor)
	{
		ShowInteractUI(false, TargetActor);
	}
	TargetActor = Actor;
	ShowInteractUI(true, TargetActor);
}



void UACInteractComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UACInteractComponent, TargetActor);
	DOREPLIFETIME(UACInteractComponent, bCurrentlyInteracting);
}