// Fill out your copyright notice in the Description page of Project Settings.

#include "FWRocketLauncher.h"
#include "Kismet/GameplayStatics.h"
#include "FWProjectile.h"
#include "Tank/FWEnemyHoverTank.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FWRocketLauncherData.h"
#include "Components/StaticMeshComponent.h"

void AFWRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
	InitialRelativeLocation = WeaponMesh->GetRelativeTransform().GetLocation();
}

void AFWRocketLauncher::UnequipWeapon()
{
	Super::UnequipWeapon();
	ChargedRocketsChargeCounter = 0.f;
	AmountRocketsCharged = 0;
	bFiringChargedRockets = false;
	WeaponMesh->SetRelativeLocation(InitialRelativeLocation);
}

void AFWRocketLauncher::AltTriggerPressed()
{
	Super::AltTriggerPressed();
	ChargedRocketsChargeCounter = 0.f;
}

void AFWRocketLauncher::AltTriggerReleased()
{
	Super::AltTriggerReleased();
	if (AmountRocketsCharged > 0)
	{
		bFiringChargedRockets = true;
		ChargedRocketsFireCounter = GetWeaponDataAs<UFWRocketLauncherData>()->TimeBetweenChargedRockets;
		ChargedRocketsChargeCounter = 0.f;
	}
}

bool AFWRocketLauncher::CanFire()
{
	return Super::CanFire() && !bFiringChargedRockets && !bAltTriggerPressed;
}

void AFWRocketLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UFWRocketLauncherData* Data = GetWeaponDataAs<UFWRocketLauncherData>();
	if (bAltTriggerPressed && AmountRocketsCharged < Data->MaxRocketsChargable && CurrentAmmo > 0)
	{
		ChargedRocketsChargeCounter += DeltaTime;
		if (ChargedRocketsChargeCounter >= Data->TimeToChargeRocket)
		{
			++AmountRocketsCharged;
			ChargedRocketsChargeCounter = 0.f;
		}
	}
	if (bFiringChargedRockets && AmountRocketsCharged > 0)
	{
		ChargedRocketsFireCounter -= DeltaTime;
		if (ChargedRocketsFireCounter <= 0.f)
		{
			FireProjectile();
			ChargedRocketsFireCounter = Data->TimeBetweenChargedRockets;
			--AmountRocketsCharged;
			if (AmountRocketsCharged == 0)
			{
				bFiringChargedRockets = false;
			}
		}
	}
	else
	{
		if (FireRateCounter > 0.f)
		{
			float FireRatePercent = 1.f - (FireRateCounter / GetFireRatePerSecond());
			FVector NewRelativeLocation = FMath::Lerp<FVector>(WeaponMesh->GetRelativeTransform().GetLocation(), InitialRelativeLocation, FireRatePercent);
			WeaponMesh->SetRelativeLocation(NewRelativeLocation);
		}
	}
}

void AFWRocketLauncher::FireProjectile()
{
	Super::FireProjectile();
	FVector CurrentLocalLocation = WeaponMesh->GetRelativeTransform().GetLocation();
	WeaponMesh->SetRelativeLocation(CurrentLocalLocation + FVector(-20.f, 0.f, 0.f));
}

int32 AFWRocketLauncher::GetChargeAmount()
{
	return AmountRocketsCharged;
}

float AFWRocketLauncher::GetChargePercent()
{
	return ChargedRocketsChargeCounter / GetWeaponDataAs<UFWRocketLauncherData>()->TimeToChargeRocket;
}
