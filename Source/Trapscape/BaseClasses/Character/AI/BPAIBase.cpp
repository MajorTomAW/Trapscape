// Fill out your copyright notice in the Description page of Project Settings.


#include "BPAIBase.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABPAIBase::ABPAIBase()
{
	GetCharacterMovement()->MaxWalkSpeed = AIInfo.Speed;
}

void ABPAIBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = AIInfo.Speed;
	AAIController* AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		BlackboardComponent->SetValueAsFloat("AttackRange", AIInfo.AttackRange);
		BlackboardComponent->SetValueAsFloat("AttackSpeed", AIInfo.AttackSpeed);
	}
}
