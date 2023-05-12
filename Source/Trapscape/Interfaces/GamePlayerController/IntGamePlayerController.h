// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trapscape/TrapscapeLibrary.h"
#include "Trapscape/UI/Shop/WShop.h"
#include "UObject/Interface.h"
#include "IntGamePlayerController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIntGamePlayerController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAPSCAPE_API IIntGamePlayerController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta=(ReturnDisplayName="PlayerController"))
		APCGamePlayerController* GetPlayerController();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void CreateShopUI(TSubclassOf<UWShop> Widget);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PurchaseBuilding(int Cost, const TArray<FBuildingInfo>& Items, UWShop* Callback);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PurchaseBuildingCallback(int PlayerMoney);
};