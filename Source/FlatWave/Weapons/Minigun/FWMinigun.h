// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWPlayerWeapon.h"
#include "FWMinigun.generated.h"

UCLASS(Blueprintable)
class FLATWAVE_API AFWMinigun : public AFWPlayerWeapon
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* MuzzleParticles;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* ShellParticles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* SpinUpSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* SpinDownSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* SpinLoopSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* FireSound;
public:
	AFWMinigun();

	void FireProjectile() override;

	void UnequipWeapon() override;

	void TriggerPressed() override;
	void TriggerReleased() override;

	void ActivateParticles();

	bool CanStartWarmup();
	bool CanFire() override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetWarmupCounter();
protected:
	void Tick(float DeltaTime) override;
	float WarmupCounter = 0.f;
	float GetWarmupPercent();
};
