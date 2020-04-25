// Fill out your copyright notice in the Description page of Project Settings.

#include "FWPlayerWeapon.h"
#include "FWWeaponData.h"
#include "FWPlayerCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "FWPlayerController.h"
#include "FWProjectileData.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "FWUtilities.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFWPlayerWeapon, Warning, All);

AFWPlayerWeapon::AFWPlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>("ProjectileSpawn");
	ProjectileSpawn->SetupAttachment(WeaponMesh);
}

void AFWPlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->SetVisibility(false);
	CurrentAmmo = WeaponData->MaxAmmo;
}

void AFWPlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FireRateCounter > 0.f)
	{
		FireRateCounter -= DeltaTime;
	}
}

void AFWPlayerWeapon::EquipWeapon()
{
	WeaponMesh->SetVisibility(true);
}

void AFWPlayerWeapon::UnequipWeapon()
{
	bTriggerPressed = false;
	bAltTriggerPressed = false;
	WeaponMesh->SetVisibility(false);
}

void AFWPlayerWeapon::TriggerPressed()
{
	if (!WeaponData)
	{
		UE_LOG(LogFWPlayerWeapon, Warning, TEXT("No WeaponData!"));
		return;
	}
	if (CurrentAmmo <= 0)
		return;
	bTriggerPressed = true;
	if (bCanFireOnPressed && CanFire())
		FireProjectile();
}

void AFWPlayerWeapon::TriggerReleased()
{
	bTriggerPressed = false;
}

void AFWPlayerWeapon::AltTriggerPressed()
{
	//UE_LOG(LogFWPlayerWeapon, Warning, TEXT("AltTriggerClicked"));
	bAltTriggerPressed = true;
}

void AFWPlayerWeapon::AltTriggerReleased()
{
	//UE_LOG(LogFWPlayerWeapon, Warning, TEXT("AltTriggerReleased"));
	bAltTriggerPressed = false;
}

bool AFWPlayerWeapon::CanFire()
{
	return CurrentAmmo >= WeaponData->AmmoCostPerShot && FireRateCounter <= 0.f && bTriggerPressed;
}

float AFWPlayerWeapon::GetSpread()
{
	return WeaponData->MaxSpread;
}

void AFWPlayerWeapon::FireProjectile()
{
	//UE_LOG(LogFWPlayerWeapon, Warning, TEXT("FireProjectileBase"));
	ConsumeAmmo();
	FireRateCounter = GetFireRatePerSecond();
	if (WeaponData->FireSound)
		UGameplayStatics::PlaySoundAtLocation(this, WeaponData->FireSound, GetActorLocation());
	if (WeaponData->ProjectileData && WeaponData->ProjectileData->ProjectileClass)
	{
		FVector Location = GetProjectileSpawnLocation();
		FRotator Rotation = GetOwnerCharacter()->GetProjectileSpawnRotation();
		FVector AimRotationStart = GetOwnerCharacter()->GetFirstPersonCameraComponent()->GetComponentLocation();
		FVector AimRotationEnd = Location + GetOwnerCharacter()->GetFirstPersonCameraComponent()->GetForwardVector() * AimAdjustmentCheckDistance;
		FHitResult AimHit;
		if (GetWorld()->LineTraceSingleByChannel(AimHit, AimRotationStart, AimRotationEnd, ECollisionChannel::ECC_Visibility))
		{
			if (AimHit.Distance > MinDistanceForAimAdjustments)
			{
				FVector AimDir = AimHit.ImpactPoint - Location;
				AimDir.Normalize();
				Rotation = AimDir.Rotation();
			}
		}
		float Spread = GetSpread();
		if (Spread > 0.f)
		{
			FVector RotationVector = Rotation.Vector();
			RotationVector = RotationVector.RotateAngleAxis(FMath::RandRange(-Spread, Spread), FVector::UpVector);
			RotationVector = RotationVector.RotateAngleAxis(FMath::RandRange(-Spread, Spread), FVector::RightVector);
			Rotation = RotationVector.Rotation();
		}
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = GetOwnerCharacter();
		AFWProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AFWProjectile>(WeaponData->ProjectileData->ProjectileClass, Location, Rotation, SpawnParams);
	}
}

void AFWPlayerWeapon::ChangeAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, 0, GetMaxAmmo());
}

int32 AFWPlayerWeapon::GetCurrentAmmo()
{
	return CurrentAmmo;
}

int32 AFWPlayerWeapon::GetMaxAmmo()
{
	return WeaponData->MaxAmmo;
}

void AFWPlayerWeapon::ConsumeAmmo()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - WeaponData->AmmoCostPerShot, 0, GetMaxAmmo());
}

class UFWWeaponData* AFWPlayerWeapon::GetWeaponData() const
{
	return WeaponData;
}

float AFWPlayerWeapon::GetFireRateCounter()
{
	return FireRateCounter;
}

float AFWPlayerWeapon::GetFireRatePerSecond()
{
	return 1 / (WeaponData->FireRate / 60.f);
}

bool AFWPlayerWeapon::IsTriggerPressed() const
{
	return bTriggerPressed;
}

bool AFWPlayerWeapon::IsAltTriggerPressed() const
{
	return bAltTriggerPressed;
}

FVector AFWPlayerWeapon::GetProjectileSpawnLocation()
{
	return ProjectileSpawn->GetComponentLocation();
}

class AFWPlayerCharacterBase* AFWPlayerWeapon::GetOwnerCharacter() const
{
	return OwnerPlayer;
}

class AFWPlayerController* AFWPlayerWeapon::GetOwnerPlayerController() const
{
	return UFWUtilities::GetFirstFWPlayerController(GetWorld());
}
