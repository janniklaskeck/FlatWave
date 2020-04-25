// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTService_RotateTurret.h"
#include "FWAIController.h"
#include "Tank/FWEnemyHoverTank.h"
#include "BehaviorTree/BlackboardComponent.h"

void UFWBTService_RotateTurret::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
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
				FVector ModifiedTargetOffset = TargetOffset;
				if (bPredictTarget)
				{
					ModifiedTargetOffset += TargetActor->GetVelocity() * PredictScale;
				}
				HoverTank->RotateTurretTowardsTarget(TargetActor, DeltaSeconds, ModifiedTargetOffset);
				HoverTank->RotateBarrelTowardsTarget(TargetActor, DeltaSeconds, ModifiedTargetOffset);
			}
		}
	}
}
