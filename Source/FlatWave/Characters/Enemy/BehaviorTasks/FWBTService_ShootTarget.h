// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "FWBTService_ShootTarget.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWBTService_ShootTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
