// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "Kismet/KismetSystemLibrary.h"


UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = "Move to Target";
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(BlackboardComponent)
	{
		AcceptableRadius = BlackboardComponent->GetValue<UBlackboardKeyType_Float>("AttackRange") - 100.0f;
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::SanitizeFloat(AcceptableRadius));
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
