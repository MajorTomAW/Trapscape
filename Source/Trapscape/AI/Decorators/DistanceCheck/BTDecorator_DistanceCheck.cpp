// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_DistanceCheck.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetSystemLibrary.h"

UBTDecorator_DistanceCheck::UBTDecorator_DistanceCheck()
{
	NodeName = "Distance Check";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
	Primary.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCheck, Primary));
	Secondary.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCheck, Secondary));
	Primary.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCheck, Primary), AActor::StaticClass());
	Secondary.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_DistanceCheck, Secondary), AActor::StaticClass());
}

bool UBTDecorator_DistanceCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bCondition = false;
	if(Primary.SelectedKeyName != FName("None") && Secondary.SelectedKeyName != FName("None"))
	{
		const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

		//Get Location
		FVector PrimaryLocation;
		//UKismetSystemLibrary::PrintString(GetWorld(), Primary.SelectedKeyType->GetName());

		//Primary
		if(Primary.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			PrimaryLocation = BlackboardComponent->GetValue<UBlackboardKeyType_Vector>(Primary.SelectedKeyName);
		}
		else
		{
			UObject* KeyValue = BlackboardComponent->GetValue<UBlackboardKeyType_Object>(Primary.SelectedKeyName);
			AActor* TargetActor = Cast<AActor>(KeyValue);
			if(TargetActor)
			{
				PrimaryLocation = TargetActor->GetActorLocation();
			}
		}

		//Secondary
		FVector SecondaryLocation;
		if(Secondary.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		{
			SecondaryLocation = BlackboardComponent->GetValue<UBlackboardKeyType_Vector>(Secondary.SelectedKeyName);
		}
		else
		{
			UObject* KeyValue = BlackboardComponent->GetValue<UBlackboardKeyType_Object>(Secondary.SelectedKeyName);
			AActor* TargetActor = Cast<AActor>(KeyValue);
			if(TargetActor)
			{
				SecondaryLocation = TargetActor->GetActorLocation();
			}
		}

		//Calculate Result
		bCondition = FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), PrimaryLocation) < FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), SecondaryLocation);
	}
	UKismetSystemLibrary::PrintString(GetWorld(), bCondition ? "Is Closer than the other" : "is not closer than the other");
	return bCondition;
}

FString UBTDecorator_DistanceCheck::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %s is closer than %s"), *Super::GetStaticDescription(), *Primary.SelectedKeyName.ToString(),*Secondary.SelectedKeyName.ToString());
}
