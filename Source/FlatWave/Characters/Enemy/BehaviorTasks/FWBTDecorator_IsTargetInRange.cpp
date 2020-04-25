// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTDecorator_IsTargetInRange.h"
#include "FWAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFWBTDecorator_IsTargetInRange::UFWBTDecorator_IsTargetInRange()
{
	NodeName = "IsTargetInRange";
}

bool UFWBTDecorator_IsTargetInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		APawn* Pawn = Controller->GetPawn();
		if (Pawn)
		{
			UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
			AActor* TargetActor = Cast<AActor>(TargetObject);
			if (TargetActor)
			{
				float Distance = FVector::Distance(Pawn->GetActorLocation(), TargetActor->GetActorLocation());
				return Distance <= MaxDistance && Distance >= MinDistance;
			}
		}
	}

	return false;
}
