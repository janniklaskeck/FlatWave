// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTDecorator_IsPointingAtTarget.h"
#include "FWAIController.h"
#include "Tank/FWEnemyHoverTank.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UFWBTDecorator_IsPointingAtTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		AFWEnemyHoverTank* HoverTank = Cast<AFWEnemyHoverTank>(Controller->GetPawn());
		if (HoverTank)
		{
			UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
			AActor* TargetActor = Cast<AActor>(TargetObject);
			if (TargetActor)
			{
				return HoverTank->IsPointingAt(TargetActor, AimingTolerance);
			}
		}
	}
	return false;
}
