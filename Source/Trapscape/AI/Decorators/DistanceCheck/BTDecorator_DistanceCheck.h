// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_DistanceCheck.generated.h"

/**
 * 
 */
UCLASS()
class TRAPSCAPE_API UBTDecorator_DistanceCheck : public UBTDecorator
{
	GENERATED_BODY()
	UBTDecorator_DistanceCheck();
public:
	UPROPERTY(EditAnywhere, Category = Decorator)
		FBlackboardKeySelector Primary;
	UPROPERTY(EditAnywhere, Category = Decorator)
		FBlackboardKeySelector Secondary;
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
};
