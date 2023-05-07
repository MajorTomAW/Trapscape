// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Trapscape/BaseClasses/Buildings/BPBuildingBase.h"
#include "BPDefense.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API ABPDefense : public ABPBuildingBase
{
	GENERATED_BODY()
	ABPDefense();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAIPerceptionStimuliSourceComponent* AIPerceptionComponent;
};
