// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/FWWeaponData.h"
#include "FWMinigunData.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWMinigunData : public UFWWeaponData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float RotationRate = 720.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float WarmupTime = 0.f;
};
