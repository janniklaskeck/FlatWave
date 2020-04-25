// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FWBTDecorator_IsTargetVisible.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API UFWBTDecorator_IsTargetVisible : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UFWBTDecorator_IsTargetVisible();
protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	UPROPERTY(EditAnywhere)
		FVector CheckOffset = FVector(0.f, 0.f, 50.f);
	UPROPERTY(EditAnywhere)
		float CheckRange = 50000.f;
};
