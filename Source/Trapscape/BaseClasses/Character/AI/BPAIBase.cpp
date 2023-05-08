// Fill out your copyright notice in the Description page of Project Settings.


#include "BPAIBase.h"

#include "GameFramework/CharacterMovementComponent.h"

ABPAIBase::ABPAIBase()
{
	GetCharacterMovement()->MaxWalkSpeed = AISpeed;
}

void ABPAIBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = AISpeed;
}
