// Fill out your copyright notice in the Description page of Project Settings.

#include "FWBTTask_MoveToTarget.h"
#include "FWAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


UFWBTTask_MoveToTarget::UFWBTTask_MoveToTarget()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
	NodeName = "MoveToTarget";
}

EBTNodeResult::Type UFWBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComponent)
		OwnerComponent = &OwnerComp;
	AFWAIController* Controller = Cast<AFWAIController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	if (TargetObject)
	{
		AActor* TargetActor = Cast<AActor>(TargetObject);
		if (TargetActor)
		{
			EPathFollowingRequestResult::Type Result = Controller->MoveToActor(TargetActor, AcceptanceRadius, true, true, bCanStrafe, NULL, false);
			if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
			{
				OnTargetReached();
				return EBTNodeResult::Succeeded;
			}
			if (bWaitForTargetReached)
			{
				Controller->OnMoveSuccessful.RemoveDynamic(this, &UFWBTTask_MoveToTarget::OnTargetReached);
				Controller->OnMoveSuccessful.AddDynamic(this, &UFWBTTask_MoveToTarget::OnTargetReached);
			}
			return bWaitForTargetReached ? EBTNodeResult::InProgress : EBTNodeResult::Succeeded;
		}
	}
	else
	{
		FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
		EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(TargetLocation, AcceptanceRadius, true, true, false, bCanStrafe, NULL, false);
		if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			OnTargetReached();
			return EBTNodeResult::Succeeded;
		}
		else if (Result == EPathFollowingRequestResult::Failed)
		{
			return EBTNodeResult::Failed;
		}
		if (bWaitForTargetReached)
		{
			Controller->OnMoveSuccessful.RemoveDynamic(this, &UFWBTTask_MoveToTarget::OnTargetReached);
			Controller->OnMoveSuccessful.AddDynamic(this, &UFWBTTask_MoveToTarget::OnTargetReached);
		}
		return bWaitForTargetReached ? EBTNodeResult::InProgress : EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void UFWBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UFWBTTask_MoveToTarget::OnTargetReached()
{
	AFWAIController* Controller = Cast<AFWAIController>(OwnerComponent->GetAIOwner());
	Controller->OnMoveSuccessful.RemoveDynamic(this, &UFWBTTask_MoveToTarget::OnTargetReached);
	FinishLatentTask(*OwnerComponent, EBTNodeResult::Succeeded);
	if (bResetBlackboardKeyOnReached)
		OwnerComponent->GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
}

