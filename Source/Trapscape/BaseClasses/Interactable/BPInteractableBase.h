// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Trapscape/Interfaces/Interacting/InteractInterface.h"
#include "Trapscape/UI/Interactable/WInteract.h"
#include "BPInteractableBase.generated.h"

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	NPC, Item, Static
};

USTRUCT(BlueprintType)
struct FInteractInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText ObjectName = FText::FromString("Object");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EInteractType InteractType = EInteractType::Static;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText InteractingText = FText::FromString("Interact with");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText InteractingKey = FText::FromString("F");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bUseProgress = true;
};

UCLASS()
class TRAPSCAPE_API ABPInteractableBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPInteractableBase();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UBoxComponent* InteractHitbox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UWidgetComponent* InteractWidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ShowInteractInterface_Implementation(bool bShow) override;
	virtual void SendIsPressed_Implementation(bool bIsPressed) override;
	virtual void InteractProgress_Implementation(float Progress) override;
	virtual void Interact_Implementation(ABPPlayerBase* Player) override;
	virtual bool GetUseProgress_Implementation() override;
	
	
	UWInteract* InteractWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interact")
		FInteractInfo InteractInfo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		bool bInteractable = true;

	UFUNCTION(Server, Reliable)
		void InteractWithObject(ABPPlayerBase* Player);
};
