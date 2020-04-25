// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner/FWSpawner.h"
#include "FWEnemyCharacterBase.h"
#include "FWEnemySpawner.generated.h"

UCLASS()
class FLATWAVE_API AFWEnemySpawner : public AFWSpawner
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* SpawnParticles;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* SpawnSound;
public:
	AFWEnemySpawner();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void SetActive(bool bIsActive);

	void SetupSpawner(int32 Amount, float Interval, bool RequireDeathForCompletion);
	bool IsDoneSpawning();
	bool AllEnemiesKilled();

	bool IsSpawningClass(UClass* Class);
protected:
	bool bIsActivated = true;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFWEnemyCharacterBase> EnemyClass;
	UPROPERTY(EditAnywhere)
		float SpawnRateSeconds = 5.f;
	float SpawnRateCounter = 0.f;
	int32 RemainingSpawns;
	int32 AmountToSpawn;

	UPROPERTY(EditAnywhere)
		bool bWaitForSpawnedEnemyDeaths = false;
	int32 SpawnedEnemyDeathAmount;

	UPROPERTY(EditDefaultsOnly)
		FVector SpawnOffset = FVector(0.f, 0.f, 100.f);
	UPROPERTY(EditDefaultsOnly)
		float SpawnRadius = 200.f;
	FVector GetSpawnLocation() override;

	UFUNCTION()
		void IncrementKilledEnemies(AActor* DestroyedActor);
};
