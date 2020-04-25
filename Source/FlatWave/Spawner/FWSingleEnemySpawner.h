// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner/FWEnemySpawner.h"
#include "FWSingleEnemySpawner.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API AFWSingleEnemySpawner : public AFWEnemySpawner
{
	GENERATED_BODY()
public:
	AActor* SpawnActor() override;
	UPROPERTY(EditDefaultsOnly)
		bool bRespawnOnDeath = true;

private:
	UFUNCTION()
		void SimpleSpawn();
};
