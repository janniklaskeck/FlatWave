// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "FWBTDecorator_IsPointingAtTarget.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API UFWBTDecorator_IsPointingAtTarget : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	UPROPERTY(EditAnywhere)
		float AimingTolerance = 5.f;
};
