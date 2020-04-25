// Fill out your copyright notice in the Description page of Project Settings.

#include "FWEnemyHoverRocketArtillery.h"
#include "FWProjectile.h"
#include "FWProjectileData.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FWHealthComponent.h"

void AFWEnemyHoverRocketArtillery::ShootProjectile(AActor* TargetActor /*= nullptr*/)
{
	if (ProjectileData)
	{
		RocketsLeftTofire = AmountRocketsPerSalvo;
		CurrentTarget = TargetActor;
		RocketFireCounter = 0.f;
		bFiringRockets = true;
	}
}

void AFWEnemyHoverRocketArtillery::RotateBarrelTowardsTarget(AActor* Target, float DeltaTime, FVector Offset /*= FVector()*/)
{
	FRotator CurrentRotation = BarrelComponent->GetComponentRotation();
	FRotator TargetRotation = CurrentRotation;
	TargetRotation.Roll = TurretComponent->GetComponentRotation().Roll;
	TargetRotation.Yaw = TurretComponent->GetComponentRotation().Yaw;
	TargetRotation.Pitch = BarrelMinPitch;
	BarrelComponent->SetWorldRotation(FMath::Lerp(CurrentRotation, TargetRotation, BarrelPitchSpeed * DeltaTime));
}

bool AFWEnemyHoverRocketArtillery::IsPointingAt(AActor* Target, float Tolerance /*= 5.f*/)
{
	if (!Target)
		return false;
	float CurrentPitch = BarrelComponent->GetComponentRotation().Pitch;
	bool IsAproxPointing = FMath::IsNearlyEqual(CurrentPitch, BarrelMinPitch, 0.5f);
	float CurrentYaw = BarrelComponent->GetComponentRotation().Yaw;
	FVector DirectionTowardsTarget = Target->GetActorLocation() - GetActorLocation();
	DirectionTowardsTarget.Normalize();
	float TargetYaw = DirectionTowardsTarget.Rotation().Yaw;
	bool IsYawCorrect = FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 0.1f);
	return IsAproxPointing && IsYawCorrect;
}

bool AFWEnemyHoverRocketArtillery::IsDoneFiring()
{
	return !bFiringRockets;
}

void AFWEnemyHoverRocketArtillery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bFiringRockets)
	{
		if (GetHealthComponent()->GetHealth() <= 0.f)
		{
			RocketsLeftTofire = 0;
		}
		RocketFireCounter -= DeltaTime;
		if (RocketsLeftTofire <= 0)
		{
			bFiringRockets = false;
		}
		else if (RocketFireCounter <= 0.f)
		{
			FireRocket(CurrentTarget);
			--RocketsLeftTofire;
			RocketFireCounter = TimeBetweenRocketFire;
		}
	}
}

void AFWEnemyHoverRocketArtillery::FireRocket(AActor* Target)
{
	if (!Target)
		return;
	FVector Velocity;
	FVector StartLocation = MuzzleLocationComponent->GetComponentLocation();
	StartLocation += MuzzleLocationComponent->GetRightVector() * FMath::RandRange(-100.f, 100.f);
	FVector TargetLocation = Target->GetActorLocation() + Target->GetVelocity() * VelocityPredictionScale;
	float CustomGravity = ProjectileData->GravityScale * GetWorld()->GetGravityZ();

	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, Velocity, StartLocation, TargetLocation, CustomGravity))
	{
		FVector MuzzleLocation = MuzzleLocationComponent->GetComponentLocation();
		FVector Direction = Velocity;
		Direction.Normalize();
		FRotator Rotation = Direction.Rotation();
		FActorSpawnParameters Params;
		Params.Instigator = this;
		AFWProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AFWProjectile>(ProjectileData->ProjectileClass, MuzzleLocation, Rotation, Params);
		if (SpawnedProjectile)
		{
			SpawnedProjectile->SetInitialVelocity(Velocity.Size());
			SpawnedProjectile->GetProjectileMovement()->HomingTargetComponent = Target->GetRootComponent();
			if (FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("wat"));
	}
}
