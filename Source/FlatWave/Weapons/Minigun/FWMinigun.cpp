// Fill out your copyright notice in the Description page of Project Settings.

#include "FWMinigun.h"
#include "FWMinigunData.h"
#include "FWProjectile.h"
#include "FWPlayerCharacterBase.h"
#include "FWProjectileData.h"
#include "FWPlayerController.h"
#include "FWDamgeTypeBase.h"
#include "FWUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "FlatWave.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

AFWMinigun::AFWMinigun()
{
	MuzzleParticles = CreateDefaultSubobject<UParticleSystemComponent>("MuzzleParticles");
	MuzzleParticles->SetupAttachment(RootComponent);
	MuzzleParticles->bAutoActivate = false;

	ShellParticles = CreateDefaultSubobject<UParticleSystemComponent>("ShellParticles");
	ShellParticles->SetupAttachment(RootComponent);
	ShellParticles->bAutoActivate = false;

	SpinUpSound = CreateDefaultSubobject<UAudioComponent>("SpinUpSound");
	SpinUpSound->SetupAttachment(RootComponent);
	SpinDownSound = CreateDefaultSubobject<UAudioComponent>("SpinDownSound");
	SpinDownSound->SetupAttachment(RootComponent);
	SpinLoopSound = CreateDefaultSubobject<UAudioComponent>("SpinLoopSound");
	SpinLoopSound->SetupAttachment(RootComponent);
	FireSound = CreateDefaultSubobject<UAudioComponent>("FireSound");
	FireSound->SetupAttachment(RootComponent);

	bCanFireOnPressed = false;
}

void AFWMinigun::FireProjectile()
{
	Super::FireProjectile();
	ActivateParticles();
	TArray<FHitResult> Hits;
	FVector Start = GetOwnerCharacter()->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector End = Start + GetOwnerCharacter()->GetFirstPersonCameraComponent()->GetForwardVector() * WeaponData->ProjectileData->MaxRange;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(COLLISION_PROJECTILE);
	bool HasHit = GetWorld()->LineTraceMultiByChannel(Hits, Start, End, COLLISION_PROJECTILE);
	if (HasHit)
	{
		for (FHitResult Hit : Hits)
		{
			if (Hit.Actor.IsValid() && Hit.Actor.Get() != GetOwner())
			{
				UFWUtilities::ApplyDamage(Hit.Actor.Get(),
										  WeaponData->ProjectileData->ImpactDamage,
										  GetOwnerPlayerController(),
										  GetOwnerCharacter(),
										  UFWDamgeTypeBase::StaticClass());
			}
		}
	}
}

void AFWMinigun::UnequipWeapon()
{
	Super::UnequipWeapon();
	FireSound->Stop();
	SpinLoopSound->Stop();
	SpinUpSound->Stop();
	SpinDownSound->Stop();
}

void AFWMinigun::TriggerPressed()
{
	Super::TriggerPressed();
	if (!bAltTriggerPressed)
	{
		FireRateCounter = GetWeaponDataAs<UFWMinigunData>()->WarmupTime;
	}
}

void AFWMinigun::TriggerReleased()
{
	Super::TriggerReleased();
	if (FireSound->IsPlaying())
	{
		FireSound->Stop();
	}
}

void AFWMinigun::ActivateParticles()
{
	ShellParticles->ActivateSystem();
	MuzzleParticles->ActivateSystem();
}

bool AFWMinigun::CanStartWarmup()
{
	return bTriggerPressed || bAltTriggerPressed;
}

bool AFWMinigun::CanFire()
{
	return (bTriggerPressed || ((bTriggerPressed && bAltTriggerPressed))) && WarmupCounter >= GetWeaponDataAs<UFWMinigunData>()->WarmupTime && CurrentAmmo > 0;
}

float AFWMinigun::GetWarmupCounter()
{
	return WarmupCounter;
}

void AFWMinigun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UFWMinigunData* Data = GetWeaponDataAs<UFWMinigunData>();
	if (FireRateCounter <= 0.f && WeaponData->bFireContinuously && CanFire())
	{
		FireProjectile();
	}
	if (CanStartWarmup())
	{
		WarmupCounter = FMath::Clamp(WarmupCounter + DeltaTime, 0.f, Data->WarmupTime);
		float WarmupPercent = GetWarmupPercent();
		if (WarmupPercent < 1.f && !SpinUpSound->IsPlaying())
		{
			SpinUpSound->Play();
		}
		float RotationRate = FMath::Lerp<float>(0, Data->RotationRate, WarmupPercent);
		FRotator Rotation(0.f, 0.f, RotationRate * DeltaTime);
		WeaponMesh->AddRelativeRotation(Rotation);
	}
	else
	{
		SpinLoopSound->Stop();
		WarmupCounter = FMath::Clamp(WarmupCounter - DeltaTime, 0.f, Data->WarmupTime);
		float WarmupPercent = GetWarmupPercent();
		if (WarmupPercent > 0.f && !SpinDownSound->IsPlaying())
		{
			SpinDownSound->Play();
		}
		float RotationRate = FMath::Lerp<float>(0, Data->RotationRate, WarmupPercent);
		FRotator Rotation(0.f, 0.f, RotationRate * DeltaTime);
		WeaponMesh->AddRelativeRotation(Rotation);
	}
	if (GetWarmupPercent() >= 1.f)
	{
		if (bTriggerPressed && !FireSound->IsPlaying())
		{
			FireSound->Play();
			SpinLoopSound->Stop();
		}
		else if (!bTriggerPressed)
		{
			if (bAltTriggerPressed && !SpinLoopSound->IsPlaying())
			{
				SpinLoopSound->Play();
			}
		}
	}
}

float AFWMinigun::GetWarmupPercent()
{
	UFWMinigunData* Data = GetWeaponDataAs<UFWMinigunData>();
	return WarmupCounter / Data->WarmupTime;
}
