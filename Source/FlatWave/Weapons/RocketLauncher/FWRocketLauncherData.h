// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FWWeaponData.h"
#include "FWRocketLauncherData.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWRocketLauncherData : public UFWWeaponData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		int32 MaxRocketsChargable = 5;
	UPROPERTY(EditDefaultsOnly)
		float TimeToChargeRocket = .7f;
	UPROPERTY(EditDefaultsOnly)
		float TimeBetweenChargedRockets = .3f;
};
