// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_DistanceTo.generated.h"

UENUM()
enum class EDistanceRule : uint8
{
	Closer,
	Further,
	Equals
};

/**
 * Checks if the distance is in relation to the distance rule
 */
UCLASS()
class TRAPSCAPE_API UBTDecorator_DistanceTo : public UBTDecorator
{
	GENERATED_BODY()
	UBTDecorator_DistanceTo();
public:
	UPROPERTY(EditAnywhere, Category = Decorator)
		FBlackboardKeySelector BlackboardKey;
	UPROPERTY(EditAnywhere, Category = Decorator)
		EDistanceRule DistanceRule;
	UPROPERTY(EditAnywhere, Category = Decorator)
		float Distance;
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
};
