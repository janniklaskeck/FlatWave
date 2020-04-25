// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FWDelegates.h"
#include "FWMainGameMode.generated.h"

UENUM()
enum class EGameState : uint8
{
	Running,
	Paused,
	GameOver_Win,
	GameOver_Lose
};

UCLASS()
class FLATWAVE_API AFWMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFWMainGameMode();
private:
	EGameState CurrentState;
protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
public:
	void UpdateRunning(float DeltaSeconds);

	void SetGamePaused(bool IsPaused);
	bool IsGamePaused();
	UFUNCTION(BlueprintCallable)
		void TogglePause();

	bool IsGameWon();
	bool IsGameLost();

	void SetGameWon();
	void SetGameLost();

	FOnAction OnGameStart;
	UPROPERTY(BlueprintAssignable)
		FOnAction OnGameWon;
	UPROPERTY(BlueprintAssignable)
		FOnAction OnGameLost;
	UFUNCTION(BlueprintCallable)
		class AFWScenarioManager* GetScenarioManager() const;
private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> PauseWidgetClass;
	UPROPERTY()
		class UUserWidget* PauseWidget;
	UPROPERTY()
		class AFWScenarioManager* ScenarioManager;
	bool bEnteredGame = false;
};
