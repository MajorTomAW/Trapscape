// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trapscape/BaseClasses/Character/BPCharacterBase.h"
#include "Trapscape/Components/InteractComponent/ACInteractComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "BPPlayerBase.generated.h"

USTRUCT(BlueprintType)
struct FPlayerMovementInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float WalkSpeed = 640.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float SprintSpeed = 920.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement|Mouse")
		float MouseSensitivity = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement|Booleans")
		bool bCanMove = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement|Booleans")
		bool bCanJump = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement|Booleans")
		bool bCanRotate = true;
};

UCLASS()
class TRAPSCAPE_API ABPPlayerBase : public ABPCharacterBase
{
	GENERATED_BODY()
public:
	ABPPlayerBase();

	//Defaults
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* ThirdPersonSpringarm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* ThirdPersonCam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UACInteractComponent* InteractComponent;
	
	//Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* MouseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* InteractAction;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	//Bindings
	void PlayerMove(const FInputActionValue& Axis);
	void PlayerMouse(const FInputActionValue& Axis);
	void PlayerJump();
	void PlayerSprint();
	void StartInteracting();
	void StopInteracting();

	//Sprinting
	UFUNCTION(BlueprintCallable)
		void SprintSwitch(bool bSprintState);
	UFUNCTION(BlueprintCallable, Server, Reliable)
		void sToggleSprint(bool bSprintState);

public:
	//Values
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Movement|Mouse")
		float MinSpringArmLength = 720.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Movement|Mouse")
		float MaxSpringArmlength = 1120.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Player|Movement")
		FPlayerMovementInfo PlayerMovementInfo;
};
