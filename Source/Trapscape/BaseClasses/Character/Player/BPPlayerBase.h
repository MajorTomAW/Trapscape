// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trapscape/BaseClasses/Character/BPCharacterBase.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "BPPlayerBase.generated.h"

/**
 * 
 */
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
	
	//Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
		UInputAction* JumpAction;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	//Bindings
	void PlayerMove(const FInputActionValue& Axis);
};
