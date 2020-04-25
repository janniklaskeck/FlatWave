// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FWPlayerWeapon.h"
#include "FWLaserRifle.generated.h"

UCLASS(Blueprintable)
class FLATWAVE_API AFWLaserRifle : public AFWPlayerWeapon
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* BeamParticles;
public:
	AFWLaserRifle();

	void UnequipWeapon() override;

	void AltTriggerReleased() override;

	bool CanFire() override;

	void FireProjectile() override;
	void FireBeam();

	void ApplyBeamDamage(AActor* Target, float Damage);
	void ActivateBeamParticles();

	void Tick(float DeltaTime) override;

private:
	float ChargeCounter;
	int32 ChargedAmmoCounter;
	float RegenAmmoCounter;
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
		float GetChargePercent();
	FVector InitialRelativeLocation;
};
