// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FWWeaponData.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	MINIGUN,
	ROCKETLAUNCHER,
	LASERSHOTGUN
};

UCLASS()
class FLATWAVE_API UFWWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		EWeaponType GetWeaponType();
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		EWeaponType Type;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bFireContinuously = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float FireRate = 60.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float MaxSpread = 0.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		int32 MaxAmmo = 100;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		int32 AmmoCostPerShot = 1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		class UFWProjectileData* ProjectileData;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Audio)
		class USoundBase* FireSound;
};
