// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTTask_ShootAtTarget.h"
#include "FWAIController.h"
#include "Tank/FWEnemyHoverTank.h"
#include "BehaviorTree/BlackboardComponent.h"

UFWBTTask_ShootAtTarget::UFWBTTask_ShootAtTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UFWBTTask_ShootAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		AFWEnemyHoverTank* HoverTank = Cast<AFWEnemyHoverTank>(Controller->GetPawn());
		if (HoverTank)
		{
			UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
			AActor* Target = Cast<AActor>(TargetObject);
			HoverTank->ShootProjectile(Target);
			bIssuedFireCommand = true;
			return EBTNodeResult::InProgress;
		}
	}
	return EBTNodeResult::Failed;
}

void UFWBTTask_ShootAtTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (bIssuedFireCommand)
	{
		AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
		if (Controller)
		{
			AFWEnemyHoverTank* HoverTank = Cast<AFWEnemyHoverTank>(Controller->GetPawn());
			if (HoverTank)
			{
				if (HoverTank->IsDoneFiring())
				{
					bIssuedFireCommand = false;
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				}
			}
		}
	}
}
