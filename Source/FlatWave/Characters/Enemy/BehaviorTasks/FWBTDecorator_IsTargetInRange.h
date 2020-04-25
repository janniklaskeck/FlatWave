// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FWBTDecorator_IsTargetInRange.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWBTDecorator_IsTargetInRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UFWBTDecorator_IsTargetInRange();

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
		float MaxDistance = 2000.f;
	UPROPERTY(EditAnywhere)
		float MinDistance = 500.f;
};
