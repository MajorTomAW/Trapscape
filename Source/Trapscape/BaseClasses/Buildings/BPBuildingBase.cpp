// Fill out your copyright notice in the Description page of Project Settings.


#include "BPBuildingBase.h"

// Sets default values
ABPBuildingBase::ABPBuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	if(!HealthComponent)
	{
		HealthComponent = CreateDefaultSubobject<UACHealthComponent>("Health Component");
	}
}

// Called when the game starts or when spawned
void ABPBuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPBuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

