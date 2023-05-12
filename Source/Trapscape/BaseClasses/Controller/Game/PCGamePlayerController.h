// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Trapscape/Interfaces/GamePlayerController/IntGamePlayerController.h"
#include "PCGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API APCGamePlayerController : public APlayerController, public IIntGamePlayerController
{
	GENERATED_BODY()
protected:
	virtual void PurchaseBuilding_Implementation(int Cost, const TArray<FBuildingInfo>& Items, UWShop* Callback) override;
	virtual void PurchaseBuildingCallback_Implementation(int PlayerMoney) override;
	virtual void CreateShopUI_Implementation(TSubclassOf<UWShop> Widget) override;
	virtual APCGamePlayerController* GetPlayerController_Implementation() override;
};
