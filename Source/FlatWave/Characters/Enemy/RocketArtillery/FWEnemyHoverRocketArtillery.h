// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank/FWEnemyHoverTank.h"
#include "FWEnemyHoverRocketArtillery.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API AFWEnemyHoverRocketArtillery : public AFWEnemyHoverTank
{
	GENERATED_BODY()
public:
	void ShootProjectile(AActor* TargetActor = nullptr) override;
	void RotateBarrelTowardsTarget(AActor* Target, float DeltaTime, FVector Offset = FVector()) override;
	bool IsPointingAt(AActor* Target, float Tolerance = 5.f) override;
	UPROPERTY(EditDefaultsOnly)
		int32 AmountRocketsPerSalvo = 8;
	UPROPERTY(EditDefaultsOnly)
		float TimeBetweenRocketFire = .3f;
	UPROPERTY(EditDefaultsOnly)
		float VelocityPredictionScale = 1.0f;

	bool IsDoneFiring() override;
protected:
	void Tick(float DeltaTime) override;

	void FireRocket(AActor* Target);
	AActor* CurrentTarget;
	int32 RocketsLeftTofire = 0;
	bool bFiringRockets;
	float RocketFireCounter;
};
