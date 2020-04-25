// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemy/Tank/FWEnemyHoverTank.h"
#include "FWEnemySuicideBot.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API AFWEnemySuicideBot : public AFWEnemyHoverTank
{
	GENERATED_BODY()
public:
	AFWEnemySuicideBot();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* BombParticleSystem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* DeathParticleSystem;

	UPROPERTY(EditDefaultsOnly)
		float ExplosionDamage = 200.f;
	UPROPERTY(EditDefaultsOnly)
		float ExplosionRadius = 400.f;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* ExplosionParticleSystem;
	UPROPERTY(EditDefaultsOnly)
		class USoundBase* ExplosionSound;

	void OnDeath() override;
public:

	void Explode();
};
