// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Trapscape/Components/HealthComponent/ACHealthComponent.h"

#include "BPCharacterBase.generated.h"

UCLASS()
class TRAPSCAPE_API ABPCharacterBase : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		UACHealthComponent* HealthComponent;
	
public:
	// Sets default values for this character's properties
	ABPCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
