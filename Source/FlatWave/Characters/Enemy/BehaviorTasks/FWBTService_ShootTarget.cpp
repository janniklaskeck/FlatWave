// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTService_ShootTarget.h"
#include "FWAIController.h"
#include "Tank/FWEnemyHoverTank.h"
#include "BehaviorTree/BlackboardComponent.h"

void UFWBTService_ShootTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		AFWEnemyHoverTank* HoverTank = Cast<AFWEnemyHoverTank>(Controller->GetPawn());
		if (HoverTank)
		{
			UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
			AActor* Target = Cast<AActor>(TargetObject);
			HoverTank->ShootProjectile(Target);
		}
	}
}
