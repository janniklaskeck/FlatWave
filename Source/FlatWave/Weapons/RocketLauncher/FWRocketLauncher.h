// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWPlayerWeapon.h"
#include "FWRocketLauncher.generated.h"

UCLASS(Blueprintable)
class FLATWAVE_API AFWRocketLauncher : public AFWPlayerWeapon
{
	GENERATED_BODY()
public:

	void BeginPlay() override;
	void UnequipWeapon() override;

	void AltTriggerPressed() override;
	void AltTriggerReleased() override;

	bool CanFire() override;

	void Tick(float DeltaTime) override;
	void FireProjectile() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetChargeAmount();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetChargePercent();

private:
		FVector InitialRelativeLocation;
	bool bFiringChargedRockets = false;
	int32 AmountRocketsCharged = 0;
	float ChargedRocketsFireCounter = 0.f;
	float ChargedRocketsChargeCounter = 0.f;
};
