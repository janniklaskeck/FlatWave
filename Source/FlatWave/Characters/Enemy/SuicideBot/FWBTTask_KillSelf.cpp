// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTTask_KillSelf.h"
#include "FWAIController.h"
#include "Tank/FWEnemyHoverTank.h"
#include "FWHealthComponent.h"

UFWBTTask_KillSelf::UFWBTTask_KillSelf()
{
	NodeName = "Kill Self";
}

EBTNodeResult::Type UFWBTTask_KillSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		AFWEnemyHoverTank* HoverTank = Cast<AFWEnemyHoverTank>(Controller->GetPawn());
		if (HoverTank)
		{
			HoverTank->GetHealthComponent()->ChangeHealth(-1.f - HoverTank->GetHealthComponent()->GetHealth());
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
