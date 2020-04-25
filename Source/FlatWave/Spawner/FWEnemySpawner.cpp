// Fill out your copyright notice in the Description page of Project Settings.

#include "FWEnemySpawner.h"
#include "FWEnemyCharacterBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "NavigationSystem/Public/NavigationSystem.h"

AFWEnemySpawner::AFWEnemySpawner()
{
	SpawnParticles = CreateDefaultSubobject<UParticleSystemComponent>("SpawnParticles");
	SpawnParticles->SetupAttachment(RootComponent);

	SpawnSound = CreateDefaultSubobject<UAudioComponent>("SpawnSound");
	SpawnSound->SetupAttachment(RootComponent);
}

void AFWEnemySpawner::BeginPlay()
{
	bSpawnOnBeginPlay = false;
	Super::BeginPlay();
}

void AFWEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsActivated && RemainingSpawns > 0)
	{
		SpawnRateCounter += DeltaTime;
		if (SpawnRateCounter > SpawnRateSeconds)
		{
			SpawnRateCounter = 0.f;
			AActor* SpawnedActor = SpawnActorInternal(EnemyClass, GetSpawnLocation(), GetSpawnRotation());
			if (SpawnedActor)
			{
				SpawnParticles->ActivateSystem();
				SpawnSound->Play();
				--RemainingSpawns;
				if (bWaitForSpawnedEnemyDeaths)
				{
					SpawnedActor->OnDestroyed.AddDynamic(this, &AFWEnemySpawner::IncrementKilledEnemies);
				}
			}
		}
	}
}

void AFWEnemySpawner::SetActive(bool bIsActive)
{
	bIsActivated = bIsActive;
}

void AFWEnemySpawner::SetupSpawner(int32 Amount, float Interval, bool RequireDeathForCompletion)
{
	RemainingSpawns = Amount;
	AmountToSpawn = Amount;
	SpawnedEnemyDeathAmount = 0;
	SpawnRateSeconds = Interval;
	SpawnRateCounter = 0.f;
	bWaitForSpawnedEnemyDeaths = RequireDeathForCompletion;
}

bool AFWEnemySpawner::IsDoneSpawning()
{
	return RemainingSpawns == 0;
}

bool AFWEnemySpawner::AllEnemiesKilled()
{
	return !bWaitForSpawnedEnemyDeaths || SpawnedEnemyDeathAmount >= AmountToSpawn;
}

bool AFWEnemySpawner::IsSpawningClass(UClass* Class)
{
	if (!Class || !EnemyClass)
		return false;
	return EnemyClass == Class;
}

FVector AFWEnemySpawner::GetSpawnLocation()
{
	FVector SpawnLocation = Super::GetSpawnLocation() + SpawnOffset;
	FNavLocation ActualLocation;
	UNavigationSystemV1::GetNavigationSystem(this)->GetRandomPointInNavigableRadius(SpawnLocation, SpawnRadius, ActualLocation);
	if (ActualLocation.HasNodeRef())
		return ActualLocation.Location + SpawnOffset;
	return SpawnLocation;
}

void AFWEnemySpawner::IncrementKilledEnemies(AActor* DestroyedActor)
{
	++SpawnedEnemyDeathAmount;
}
