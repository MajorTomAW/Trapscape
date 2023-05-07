// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_DistanceTo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetSystemLibrary.h"

UBTDecorator_DistanceTo::UBTDecorator_DistanceTo()
{
	NodeName = "Distance To";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
	Distance = 500.0f;
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceTo, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceTo, BlackboardKey));

	bAllowAbortChildNodes = false;
}

bool UBTDecorator_DistanceTo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = false;
	if(BlackboardKey.SelectedKeyName != FName("None"))
	{
		const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		FVector TargetLocation;
		if(BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			TargetLocation = BlackboardComponent->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.SelectedKeyName);
		}
		else
		{
			UObject* KeyValue = BlackboardComponent->GetValue<UBlackboardKeyType_Object>(BlackboardKey.SelectedKeyName);
			AActor* TargetActor = Cast<AActor>(KeyValue);
			if(TargetActor)
			{
				TargetLocation = TargetActor->GetActorLocation();
			}
		}

		//Calculate Result
		switch (DistanceRule)
		{
		case EDistanceRule::Closer:
			bResult = FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), TargetLocation) < Distance;
			break;
		case EDistanceRule::Equals:
			bResult = FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), TargetLocation) == Distance;
			break;
		case EDistanceRule::Further:
			bResult = FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), TargetLocation) > Distance;
			break;
		}
	}
	return bResult;
}

FString UBTDecorator_DistanceTo::GetStaticDescription() const
{
	FString EnumValue = UEnum::GetValueAsString(DistanceRule).Replace(TEXT("EDistanceCheck::"), TEXT(""), ESearchCase::CaseSensitive);
	return FString::Printf(TEXT("%s: %s is %s than %.1f"), *Super::GetStaticDescription(), *BlackboardKey.SelectedKeyName.ToString(), *EnumValue, Distance);
}
