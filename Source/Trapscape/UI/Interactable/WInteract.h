// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WInteract.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API UWInteract : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* RadialProgress;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ObjectName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* InteractKey;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* InteractText;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* Interacting;
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		void SetupInteractUI(FText TextInteract, FText TextObjectName, bool bUseProgress);
	void UpdateProgress(float Progress);
	void SendIsPressed(bool bIsPressed);
};
