// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FWFloatingDamageComponent.generated.h"

UCLASS()
class FLATWAVE_API UFWFloatingDamageComponent : public UWidgetComponent
{
	GENERATED_BODY()
protected:
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UPROPERTY(EditDefaultsOnly)
		float TimeToDestroy = 1.f;
	UPROPERTY(EditDefaultsOnly)
		float MoveSpeed = 100.f;
public:
	void SetDamageValue(float DamageValue);
private:
	float DestroyCounter;
};
