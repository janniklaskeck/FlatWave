// Fill out your copyright notice in the Description page of Project Settings.

#include "FWLaserRifle.h"
#include "FWLaserRifleData.h"
#include "FWDamgeTypeBase.h"
#include "FWPlayerCharacterBase.h"
#include "FWPlayerController.h"
#include "FlatWave.h"
#include "FWUtilities.h"
#include "FWProjectileData.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

AFWLaserRifle::AFWLaserRifle()
{
	BeamParticles = CreateDefaultSubobject<UParticleSystemComponent>("BeamParticles");
	BeamParticles->SetupAttachment(WeaponMesh);
	BeamParticles->bAutoActivate = false;
	InitialRelativeLocation = WeaponMesh->GetRelativeTransform().GetLocation();
}

void AFWLaserRifle::UnequipWeapon()
{
	Super::UnequipWeapon();
	ChargeCounter = 0.f;
	WeaponMesh->SetRelativeLocation(InitialRelativeLocation);
	ChangeAmmo(ChargedAmmoCounter);
}

void AFWLaserRifle::AltTriggerReleased()
{
	Super::AltTriggerReleased();
	if (ChargedAmmoCounter > GetWeaponDataAs<UFWLaserRifleData>()->MinChargeAmount)
	{
		FireBeam();
	}
	else
	{
		ChangeAmmo(ChargedAmmoCounter);
	}
	ChargedAmmoCounter = 0;
	ChargeCounter = 0.f;
}

bool AFWLaserRifle::CanFire()
{
	return Super::CanFire() && !bAltTriggerPressed;
}

void AFWLaserRifle::FireProjectile()
{
	Super::FireProjectile();
	FVector CurrentLocalLocation = WeaponMesh->GetRelativeTransform().GetLocation();
	WeaponMesh->SetRelativeLocation(CurrentLocalLocation + FVector(-20.f, 0.f, 0.f));
}

void AFWLaserRifle::FireBeam()
{
	UFWLaserRifleData* Data = GetWeaponDataAs<UFWLaserRifleData>();
	ActivateBeamParticles();
	TArray<FHitResult> Hits;
	FVector Start = GetOwnerCharacter()->GetFirstPersonCameraComponent()->GetComponentLocation();
	float Range = FMath::Lerp(WeaponData->ProjectileData->MaxRange, Data->MaxChargeRange, GetChargePercent());
	FVector End = Start + GetOwnerCharacter()->GetFirstPersonCameraComponent()->GetForwardVector() * Range;
	bool HasHit = GetWorld()->LineTraceMultiByChannel(Hits, Start, End, COLLISION_PROJECTILE);
	if (HasHit)
	{
		for (FHitResult Hit : Hits)
		{
			if (Hit.Actor.IsValid() && Hit.Actor.Get() != GetOwner())
			{
				int32 Damage = (int)FMath::Lerp(WeaponData->ProjectileData->ImpactDamage, Data->FullChargeDamage, GetChargePercent());
				ApplyBeamDamage(Hit.Actor.Get(), Damage);
			}
		}
	}
	if (Data->LaserBeamFireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Data->LaserBeamFireSound, Start);
	}
}

void AFWLaserRifle::ApplyBeamDamage(AActor* Target, float Damage)
{
	UFWUtilities::ApplyDamage(Target, Damage, GetOwnerPlayerController(), GetOwnerCharacter(), UFWDamgeTypeBase::StaticClass());
}

void AFWLaserRifle::ActivateBeamParticles()
{
	BeamParticles->ActivateSystem();
}

void AFWLaserRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UFWLaserRifleData* Data = GetWeaponDataAs<UFWLaserRifleData>();
	if (bAltTriggerPressed)
	{
		if (ChargedAmmoCounter < Data->FullChargeAmmoCost)
		{
			ChargeCounter += DeltaTime;
			if (ChargeCounter > (Data->FullChargeTime / Data->FullChargeAmmoCost))
			{
				ChangeAmmo(-1);
				++ChargedAmmoCounter;
				ChargeCounter = 0.f;
			}
		}
	}
	else
	{
		RegenAmmoCounter += DeltaTime * Data->AmmoRechargeRate;
		if (RegenAmmoCounter > 1.f)
		{
			ChangeAmmo(1);
			RegenAmmoCounter = 0.f;
		}
	}
	if (WeaponData->bFireContinuously && CanFire())
	{
		FireProjectile();
	}
	if (FireRateCounter > 0.f)
	{
		float FireRatePercent = 1.f - (FireRateCounter / GetFireRatePerSecond());
		FVector NewRelativeLocation = FMath::Lerp<FVector>(WeaponMesh->GetRelativeTransform().GetLocation(), InitialRelativeLocation, FireRatePercent);
		WeaponMesh->SetRelativeLocation(NewRelativeLocation);
	}
}

float AFWLaserRifle::GetChargePercent()
{
	return (float)ChargedAmmoCounter / GetWeaponDataAs<UFWLaserRifleData>()->FullChargeAmmoCost;
}
