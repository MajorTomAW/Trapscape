// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Trapscape/BaseClasses/Character/Player/BPPlayerBase.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAPSCAPE_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ShowInteractInterface(bool bShow);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void InteractProgress(float Progress);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SendIsPressed(bool bIsPressed);
	UFUNCTION(BlueprintNativeEvent)
		void Interact(ABPPlayerBase* Player);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool GetUseProgress();	
};
