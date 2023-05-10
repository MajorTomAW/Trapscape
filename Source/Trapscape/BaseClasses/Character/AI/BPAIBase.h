// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trapscape/BaseClasses/Character/BPCharacterBase.h"
#include "Trapscape/Interfaces/AI/AIInterface.h"
#include "BPAIBase.generated.h"

USTRUCT(BlueprintType, DisplayName = "AI Info")
struct FAIInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed = 500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackSpeed = 3.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackRange = 300.0f;
};
/**
 * 
 */
UCLASS()
class TRAPSCAPE_API ABPAIBase : public ABPCharacterBase, public IAIInterface
{
	GENERATED_BODY()
	ABPAIBase();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI", DisplayName = "AI Info")
		FAIInfo AIInfo;

protected:
	virtual void BeginPlay() override;
};
