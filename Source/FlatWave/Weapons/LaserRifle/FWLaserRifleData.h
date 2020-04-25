// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FWWeaponData.h"
#include "FWLaserRifleData.generated.h"

UCLASS()
class FLATWAVE_API UFWLaserRifleData : public UFWWeaponData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		float FullChargeTime = 2.f;
	UPROPERTY(EditDefaultsOnly)
		int32 MinChargeAmount = 5;
	UPROPERTY(EditDefaultsOnly)
		float MaxChargeRange = 4000.f;
	UPROPERTY(EditDefaultsOnly)
		float FullChargeDamage = 80.f;
	UPROPERTY(EditDefaultsOnly)
		int32 FullChargeAmmoCost = 40;
	UPROPERTY(EditDefaultsOnly)
		float AmmoRechargeRate = 5.f;
	UPROPERTY(EditDefaultsOnly)
		class USoundBase* LaserBeamFireSound;
};
