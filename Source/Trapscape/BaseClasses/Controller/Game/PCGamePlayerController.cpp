// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGamePlayerController.h"
#include "Trapscape/Interfaces/GamePlayerController/IntGamePlayerController.h"

void APCGamePlayerController::PurchaseBuilding_Implementation(int Cost, const TArray<FBuildingInfo>& Items,
	UWShop* Callback)
{
	IIntGamePlayerController::PurchaseBuilding_Implementation(Cost, Items, Callback);
}

void APCGamePlayerController::PurchaseBuildingCallback_Implementation(int PlayerMoney)
{
	IIntGamePlayerController::PurchaseBuildingCallback_Implementation(PlayerMoney);
}

void APCGamePlayerController::CreateShopUI_Implementation(TSubclassOf<UWShop> Widget)
{
	IIntGamePlayerController::CreateShopUI_Implementation(Widget);
}

APCGamePlayerController* APCGamePlayerController::GetPlayerController_Implementation()
{
	return this;
}
