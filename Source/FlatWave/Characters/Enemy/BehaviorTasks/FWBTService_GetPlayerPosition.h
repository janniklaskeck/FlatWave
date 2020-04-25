// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "FWBTService_GetPlayerPosition.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API UFWBTService_GetPlayerPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UPROPERTY(EditAnywhere)
		float TraceDownDistance = 1000.f;
	UPROPERTY(EditAnywhere)
		float TraceCheckOffsetZ = 100.f;
	UPROPERTY(EditAnywhere)
		FVector QueryExtent;
	UPROPERTY(EditAnywhere, Category = Blackboard)
		struct FBlackboardKeySelector PlayerBlackboardKey;
};
