// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FWBTTask_KillSelf.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWBTTask_KillSelf : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UFWBTTask_KillSelf();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
