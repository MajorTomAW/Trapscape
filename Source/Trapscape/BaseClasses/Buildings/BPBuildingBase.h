// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trapscape/Components/HealthComponent/ACHealthComponent.h"
#include "BPBuildingBase.generated.h"

UCLASS()
class TRAPSCAPE_API ABPBuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPBuildingBase();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UACHealthComponent* HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
