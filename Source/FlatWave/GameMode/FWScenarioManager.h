// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWEnemySpawner.h"
#include "FWScenarioManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageAction, int32, StageIndex);

USTRUCT()
struct FSpawnerList
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<class AFWEnemySpawner*> Spawners;
	UPROPERTY(EditAnywhere)
		class UFWGameScenario* Scenario;

	TArray<class AFWEnemySpawner*> GetSpawnerForEnemyClass(TSubclassOf<class AFWEnemyCharacterBase> EnemyClass)
	{
		return Spawners.FilterByPredicate([EnemyClass](AFWEnemySpawner* Spawner)
		{
			return Spawner->IsSpawningClass(EnemyClass);
		});
	}
};

UCLASS()
class FLATWAVE_API AFWScenarioManager : public AActor
{
	GENERATED_BODY()
public:
	AFWScenarioManager();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ActivateNextStage();
	FOnStageAction OnStageStart;
	FOnStageAction OnStageEnd;
private:
	UPROPERTY(EditAnywhere)
		TArray<FSpawnerList> StageSpawners;
	bool bNotStarted = true;
	int32 CurrentStage = 0;
	int32 CurrentWave = 0;

	void ProcessStage(int32 Index);
	bool IsStageFinished(int32 Index);
	bool bStageWasFinished = false;

	void ProcessWave(int32 Index);
	bool IsWaveFinished(int32 Index);

	void SetupEnemySpawners(TSubclassOf<class AFWEnemyCharacterBase> EnemyClass, int32 Amount, float SpawnInterval, bool RequireDeathForCompletion);
};
