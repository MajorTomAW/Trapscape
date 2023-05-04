// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BPInteractableBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "BPInteractNPC.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API ABPInteractNPC : public ABPInteractableBase
{
	GENERATED_BODY()
	ABPInteractNPC();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* NPCMesh;
};
