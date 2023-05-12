// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "WGameOverlay.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API UWGameOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* Healthbar;

public:
	UFUNCTION(BlueprintCallable)
		void UpdateHealthbar(float HealthPercentage);
};
