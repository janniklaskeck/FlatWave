// Fill out your copyright notice in the Description page of Project Settings.

#include "FWAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FWEnemyCharacterBase.h"
#include "FWPlayerCharacterBase.h"
#include "FWUtilities.h"

AFWAIController::AFWAIController()
{
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorComponent");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");

	TargetPlayerKeyName = "TargetPlayer";
}

void AFWAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFWAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	AFWEnemyCharacterBase* EnemyCharacter = Cast<AFWEnemyCharacterBase>(InPawn);
	if (EnemyCharacter && EnemyCharacter->BehaviorTree)
	{
		if (EnemyCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*EnemyCharacter->BehaviorTree->BlackboardAsset);
		}
		BehaviorComponent->StartTree(*EnemyCharacter->BehaviorTree);
	}
	// DEBUG
	SetTargetPlayer(UFWUtilities::GetPlayerCharacter(this));
}

void AFWAIController::UnPossess()
{
	Super::UnPossess();
	BehaviorComponent->StopTree();
	Destroy();
}

void AFWAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.Code == EPathFollowingResult::Type::Success)
	{
		OnMoveSuccessful.Broadcast();
	}
	else if (Result.Code == EPathFollowingResult::Type::Aborted
			 || Result.Code == EPathFollowingResult::Type::Blocked
			 || Result.Code == EPathFollowingResult::Type::Invalid)
	{
		OnMoveFailed.Broadcast();
	}

	OnMoveDone.Broadcast();
}

void AFWAIController::SetTargetPlayer(class AFWPlayerCharacterBase* Player)
{
	if (BlackboardComponent)
		BlackboardComponent->SetValueAsObject(TargetPlayerKeyName, Player);
}
