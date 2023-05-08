// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trapscape/BaseClasses/Character/BPCharacterBase.h"
#include "BPAIBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API ABPAIBase : public ABPCharacterBase
{
	GENERATED_BODY()
	ABPAIBase();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI|Movement", DisplayName = "AI Speed")
		float AISpeed = 200.0f;

protected:
	virtual void BeginPlay() override;
};
