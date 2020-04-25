// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FWProjectile.h"
#include "FWProjectileData.generated.h"

UENUM()
enum class EProjectileType : uint8
{
	NONE,
	HITSCAN,
	PROJECTILE
};

UCLASS()
class FLATWAVE_API UFWProjectileData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		EProjectileType Type;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float ImpactDamage = 100;

	// HITSCAN
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = HITSCAN)
		float MaxRange = 5000.f;
	// PROJECTILE
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		float InitialVelocity = 1000.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		float Lifetime = 5.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		TSubclassOf<class AFWProjectile> ProjectileClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		float GravityScale = 0.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		bool bDestroyOnHit = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		bool bCanBeHitByProjectiles = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		class UParticleSystem* OnDestroyParticleSystem;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Audio)
		class USoundBase* OnDestroySound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		bool bExplodeOnHit = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		bool bScaleExplosionDamageWithDistance = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		float ExplosionDamage = 100.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = PROJECTILE)
		float ExplosionRange = 200.f;

	UPROPERTY(EditDefaultsOnly)
		class USoundBase* MovementSound;
};
