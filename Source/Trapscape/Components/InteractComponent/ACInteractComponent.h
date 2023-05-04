// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "ACInteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAPSCAPE_API UACInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UACInteractComponent();

protected:
	virtual void BeginPlay() override;

	void ScanInteract();
	UPROPERTY(Replicated)
		AActor* TargetActor;
	UPROPERTY(Replicated)
		bool bCurrentlyInteracting;

public:
	//Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ScanRange = 1200.0f;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	FTimerHandle InteractTimerHandle;
	FTimerDelegate TimerDelegate;
	UCameraComponent* PlayerCameraComponent;
	
	UFUNCTION(Server, Reliable)
		void StartScanning();
	UFUNCTION(Server, Reliable)
		void NewOverlap(AActor* Actor);
	UFUNCTION(Server, Reliable)
		void EndOverlap();
	UFUNCTION(Client, Reliable)
		void ShowInteractUI(bool bShow, AActor* Actor);
	UFUNCTION(Server, Reliable)
		void HandleTimer(bool bPause);
	UFUNCTION(Server, Reliable)
		void StartInteracting();
	UFUNCTION(Server, Reliable)
		void StopInteracting();
};
