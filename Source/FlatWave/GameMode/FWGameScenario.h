// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FWEnemyCharacterBase.h"
#include "FWGameScenario.generated.h"

USTRUCT()
struct FGameWaveDetails
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFWEnemyCharacterBase> EnemyClass;
	UPROPERTY(EditDefaultsOnly)
		int32 SpawnAmount = 1;
	UPROPERTY(EditDefaultsOnly)
		float SpawnInterval;
	UPROPERTY(EditDefaultsOnly)
		bool bRequireDeathForCompletion = true;
};

USTRUCT()
struct FGameWave
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TArray<FGameWaveDetails> Enemies;
};

UCLASS()
class FLATWAVE_API UFWGameScenario : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TArray<FGameWave> Waves;
};
