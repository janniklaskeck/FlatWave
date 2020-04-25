// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWScenarioGate.generated.h"

UCLASS()
class FLATWAVE_API AFWScenarioGate : public AActor
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Activate();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Deactivate();
	UPROPERTY(EditAnywhere)
		int32 StartStageIndex = -1;
	UPROPERTY(EditAnywhere)
		bool bDeactivateOnStart = false;
	UPROPERTY(EditAnywhere)
		int32 EndStageIndex = -1;
	UPROPERTY(EditAnywhere)
		bool bActivateOnEnd = false;
private:
	UFUNCTION()
		void BindActions();
	UFUNCTION()
		void CheckForActivation(int32 Index);
	UFUNCTION()
		void CheckForDeactivation(int32 Index);
};
