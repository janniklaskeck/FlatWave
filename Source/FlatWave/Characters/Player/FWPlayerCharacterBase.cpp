// Fill out your copyright notice in the Description page of Project Settings.

#include "FWPlayerCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "FWRocketLauncher.h"
#include "FWMinigun.h"
#include "FWHealthComponent.h"
#include "FWPlayerController.h"
#include "FlatWave.h"
#include "Kismet/GameplayStatics.h"
#include "FWPlayerWeapon.h"
#include "FWUtilities.h"
#include "FWMainGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(LogFWPlayerCharacter, Warning, All);

AFWPlayerCharacterBase::AFWPlayerCharacterBase()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	LaserRifleChildActor = CreateDefaultSubobject<UChildActorComponent>("LaserRifle");
	LaserRifleChildActor->SetupAttachment(FirstPersonCameraComponent);

	MinigunChildActor = CreateDefaultSubobject<UChildActorComponent>("Minigun");
	MinigunChildActor->SetupAttachment(FirstPersonCameraComponent);

	RocketLauncherChildActor = CreateDefaultSubobject<UChildActorComponent>("RocketLauncher");
	RocketLauncherChildActor->SetupAttachment(FirstPersonCameraComponent);
}

void AFWPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AFWPlayerWeapon* LaserRifle = Cast<AFWPlayerWeapon>(LaserRifleChildActor->GetChildActor());
	if (LaserRifle)
	{
		LaserRifle->OwnerPlayer = this;
		WeaponList.Add(LaserRifle);
	}
	AFWPlayerWeapon* Minigun = Cast<AFWPlayerWeapon>(MinigunChildActor->GetChildActor());
	if (Minigun)
	{
		Minigun->OwnerPlayer = this;
		WeaponList.Add(Minigun);
	}
	AFWPlayerWeapon* RocketLauncher = Cast<AFWPlayerWeapon>(RocketLauncherChildActor->GetChildActor());
	if (RocketLauncher)
	{
		RocketLauncher->OwnerPlayer = this;
		WeaponList.Add(RocketLauncher);
	}
	if (WeaponList.Num() > 0)
		EquipWeapon(0);
}


void AFWPlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDying)
	{
		DyingCounter = FMath::Clamp(DyingCounter + DeltaTime, 0.f, TimeToDeath);
		FRotator NewRotation = FMath::Lerp(PreDeathRotation, FRotator(PreDeathRotation.Pitch, PreDeathRotation.Yaw, 90.f), DyingCounter);
		SetActorRotation(NewRotation);
	}

	if (GetVelocity().SizeSquared() > 0.f && GetMovementComponent()->IsMovingOnGround() && FootStepSound)
	{
		FootStepCounter += DeltaTime;
		if (FootStepCounter > FootStepInterval)
		{
			FootStepCounter = 0.f;
			UGameplayStatics::PlaySoundAtLocation(this, FootStepSound, GetActorLocation());
		}
	}
	else if (FootStepCounter > 0.f)
	{
		FootStepCounter = 0.f;
	}
}

void AFWPlayerCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	bCanDodge = true;
}

void AFWPlayerCharacterBase::EquipWeapon(int32 Index)
{
	if (CurrentWeapon && CurrentWeapon != WeaponList[Index])
	{
		CurrentWeapon->UnequipWeapon();
	}
	CurrentWeapon = WeaponList[Index];
	if (CurrentWeapon)
	{
		CurrentWeaponIndex = Index;
		CurrentWeapon->EquipWeapon();
	}
}

int32 AFWPlayerCharacterBase::GetCurrentWeaponIndex() const
{
	return CurrentWeaponIndex;
}

class AFWPlayerWeapon* AFWPlayerCharacterBase::GetWeaponAt(int32 Index) const
{
	if (Index < 0 || Index >= WeaponList.Num())
	{
		return nullptr;
	}
	return WeaponList[Index];
}

TArray<class AFWPlayerWeapon*> AFWPlayerCharacterBase::GetWeapons() const
{
	return WeaponList;
}

float AFWPlayerCharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!Cast<AFWPlayerController>(EventInstigator))
	{
		OnDamageTaken.Broadcast();
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}
	return 0.f;
}

void AFWPlayerCharacterBase::OnDeath()
{
	AFWPlayerController* PlayerController = GetController<AFWPlayerController>();
	if (PlayerController)
	{
		PlayerController->Disable();
		bIsDying = true;
		PreDeathRotation = GetActorRotation();
		GetFirstPersonCameraComponent()->bUsePawnControlRotation = false;
	}
	UFWUtilities::GetFWMainGameMode(this)->SetGameLost();
}

class AFWPlayerWeapon* AFWPlayerCharacterBase::GetCurrentWeapon() const
{
	return CurrentWeapon;
}

FRotator AFWPlayerCharacterBase::GetProjectileSpawnRotation()
{
	return GetControlRotation();
}

void AFWPlayerCharacterBase::OnTriggerPressed()
{
	if (CurrentWeapon)
		CurrentWeapon->TriggerPressed();
}

void AFWPlayerCharacterBase::OnTriggerReleased()
{
	if (CurrentWeapon)
		CurrentWeapon->TriggerReleased();
}

void AFWPlayerCharacterBase::OnAltTriggerPressed()
{
	if (CurrentWeapon)
		CurrentWeapon->AltTriggerPressed();
}

void AFWPlayerCharacterBase::OnAltTriggerReleased()
{
	if (CurrentWeapon)
		CurrentWeapon->AltTriggerReleased();
}

void AFWPlayerCharacterBase::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFWPlayerCharacterBase::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFWPlayerCharacterBase::JumpPressed()
{
	if (CanJump())
	{
		if (JumpSound)
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
		Jump();
	}
}

void AFWPlayerCharacterBase::JumpReleased()
{
	StopJumping();
}

void AFWPlayerCharacterBase::DodgePressed()
{
	if (bCanDodge)
	{
		FVector CurrentMoveDirection = GetMovementComponent()->GetLastInputVector();
		if (CurrentMoveDirection.Size() < 0.1f)
			return;
		bCanDodge = false;
		CurrentMoveDirection.Z = DodgeVerticalPart;
		CurrentMoveDirection.Normalize();
		FVector LaunchVelocity = CurrentMoveDirection * DodgeVelocity;
		LaunchCharacter(LaunchVelocity, true, true);
	}
}
