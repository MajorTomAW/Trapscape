// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WShop.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API UWShop : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdatePlayerMoney(int Money);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int PlayerMoney = 0;
	
};
