// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemy/FWEnemyCharacterBase.h"
#include "FWEnemyHoverTank.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API AFWEnemyHoverTank : public AFWEnemyCharacterBase
{
	GENERATED_BODY()
public:
	AFWEnemyHoverTank();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ChassisComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TurretComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BarrelComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* MuzzleLocationComponent;

	UPROPERTY()
		TArray<class UMaterialInstanceDynamic*> ChassisMaterialInstances;
	UPROPERTY()
		TArray<class UMaterialInstanceDynamic*> TurretMaterialInstances;
	UPROPERTY()
		TArray<class UMaterialInstanceDynamic*> BarrelMaterialInstances;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

public:
	void RotateTurretTowardsTarget(AActor* Target, float DeltaTime, FVector Offset = FVector());
	virtual void RotateBarrelTowardsTarget(AActor* Target, float DeltaTime, FVector Offset = FVector());
	UPROPERTY(EditDefaultsOnly)
		float TurretRotationSpeed = 15.f;
	UPROPERTY(EditDefaultsOnly)
		float BarrelPitchSpeed = 5.f;
	UPROPERTY(EditDefaultsOnly)
		float BarrelMinPitch = -10.f;
	UPROPERTY(EditDefaultsOnly)
		float BarrelMaxPitch = 45.f;

	virtual bool IsPointingAt(AActor* Target, float Tolerance = 5.f);

	UPROPERTY(EditDefaultsOnly)
		class UFWProjectileData* ProjectileData;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Audio)
		class USoundBase* FireSound;
	virtual void ShootProjectile(AActor* TargetActor = nullptr);
	virtual bool IsDoneFiring();
protected:
	virtual void OnDeath() override;
	bool bIsDying = false;
	UPROPERTY(EditDefaultsOnly)
		float DissolveDelay = 1.0f;
	float DissolveCounter;
};
