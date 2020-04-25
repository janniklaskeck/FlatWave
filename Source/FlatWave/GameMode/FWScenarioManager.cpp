// Fill out your copyright notice in the Description page of Project Settings.

#include "FWScenarioManager.h"
#include "FWGameScenario.h"
#include "FWUtilities.h"
#include "FWEnemyCharacterBase.h"
#include "FWMainGameMode.h"

AFWScenarioManager::AFWScenarioManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFWScenarioManager::BeginPlay()
{
	Super::BeginPlay();

}

void AFWScenarioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bNotStarted)
	{
		if (IsWaveFinished(CurrentWave))
		{
			if (CurrentWave < StageSpawners[CurrentStage].Scenario->Waves.Num() - 1)
			{
				++CurrentWave;
				ProcessWave(CurrentWave);
			}
		}
		if (IsStageFinished(CurrentStage) && !bStageWasFinished)
		{
			OnStageEnd.Broadcast(CurrentStage);
			UE_LOG(LogTemp, Warning, TEXT("Stage Finished: %d"), CurrentStage);
			if (CurrentStage == StageSpawners.Num() - 1)
			{
				UFWUtilities::GetFWMainGameMode(this)->SetGameWon();
			}
			bStageWasFinished = true;
		}
	}
}

void AFWScenarioManager::ActivateNextStage()
{
	bStageWasFinished = false;
	if (bNotStarted)
	{
		ProcessStage(0);
		bNotStarted = false;
	}
	else
	{
		ProcessStage(CurrentStage + 1);
	}
}

void AFWScenarioManager::ProcessStage(int32 Index)
{
	if (Index > StageSpawners.Num() - 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("No more stages left!"));
		return;
	}
	CurrentStage = Index;
	UE_LOG(LogTemp, Warning, TEXT("Process Stage: %d"), CurrentStage);
	OnStageStart.Broadcast(CurrentStage);
	CurrentWave = 0;
	ProcessWave(CurrentWave);
}

bool AFWScenarioManager::IsStageFinished(int32 Index)
{
	bool IsLastWave = CurrentWave == StageSpawners[CurrentStage].Scenario->Waves.Num() - 1;
	return IsLastWave && IsWaveFinished(CurrentWave);
}

bool AFWScenarioManager::IsWaveFinished(int32 Index)
{
	for (AFWEnemySpawner* Spawner : StageSpawners[CurrentStage].Spawners)
	{
		if (!(Spawner->IsDoneSpawning() && Spawner->AllEnemiesKilled()))
			return false;
	}
	return true;
}

void AFWScenarioManager::ProcessWave(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Process Wave: %d"), Index);
	FGameWave Wave = StageSpawners[CurrentStage].Scenario->Waves[Index];
	for (const FGameWaveDetails WaveDetails : Wave.Enemies)
	{
		SetupEnemySpawners(WaveDetails.EnemyClass, WaveDetails.SpawnAmount, WaveDetails.SpawnInterval, WaveDetails.bRequireDeathForCompletion);
	}
}

void AFWScenarioManager::SetupEnemySpawners(TSubclassOf<class AFWEnemyCharacterBase> EnemyClass, int32 Amount, float SpawnInterval, bool RequireDeathForCompletion)
{
	if (Amount == 0 || !EnemyClass)
	{
		return;
	}
	TArray<AFWEnemySpawner*> FittingSpawners = StageSpawners[CurrentStage].GetSpawnerForEnemyClass(EnemyClass);
	if (FittingSpawners.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No fitting spawners for class %s found!"), *EnemyClass->GetName());
		return;
	}
	int32 AmountPerSpawner = Amount / FittingSpawners.Num();
	int32 SpawnsLeft = Amount;
	UFWUtilities::ShuffleArray<AFWEnemySpawner*>(FittingSpawners);
	for (int32 Index = 0; Index < FittingSpawners.Num(); Index++)
	{
		AFWEnemySpawner* Spawner = FittingSpawners[Index];
		int32 ActualAmount = AmountPerSpawner;
		if (AmountPerSpawner == 0)
		{
			ActualAmount = 1;
		}
		else if (Index == FittingSpawners.Num() - 1)
		{
			// Fill last spawner
			ActualAmount = SpawnsLeft;
		}
		SpawnsLeft -= ActualAmount;
		Spawner->SetupSpawner(ActualAmount, SpawnInterval, RequireDeathForCompletion);
		if (SpawnsLeft <= 0)
		{
			break;
		}
	}
}

