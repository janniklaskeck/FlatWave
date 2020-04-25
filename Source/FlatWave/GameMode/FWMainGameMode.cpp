// Fill out your copyright notice in the Description page of Project Settings.

#include "FWMainGameMode.h"
#include "FWScenarioManager.h"
#include "Kismet/GameplayStatics.h"
#include "UserWidget.h"
#include "FWPlayerController.h"
#include "FWUtilities.h"

AFWMainGameMode::AFWMainGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFWMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> ScenarioManagers;
	UGameplayStatics::GetAllActorsOfClass(this, AFWScenarioManager::StaticClass(), ScenarioManagers);
	if (ScenarioManagers.Num() > 0)
	{
		ScenarioManager = Cast<AFWScenarioManager>(ScenarioManagers[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO SCENARIO MANAGER PRESENT!"));
	}
}

void AFWMainGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentState == EGameState::Running)
	{
		UpdateRunning(DeltaSeconds);
	}
}

void AFWMainGameMode::UpdateRunning(float DeltaSeconds)
{
	if (!bEnteredGame)
	{
		OnGameStart.Broadcast();
		bEnteredGame = true;
		AFWPlayerController* PlayerController = UFWUtilities::GetFirstFWPlayerController(this);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void AFWMainGameMode::SetGamePaused(bool IsPaused)
{
	if (IsPaused)
	{
		CurrentState = EGameState::Paused;
		UGameplayStatics::SetGamePaused(this, true);
		if (!PauseWidget && PauseWidgetClass)
		{
			PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
			PauseWidget->AddToViewport();
		}
		else
		{
			PauseWidget->SetVisibility(ESlateVisibility::Visible);
		}
		AFWPlayerController* PlayerController = UFWUtilities::GetFirstFWPlayerController(this);
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		CurrentState = EGameState::Running;
		UGameplayStatics::SetGamePaused(this, false);
		if (PauseWidget)
			PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		AFWPlayerController* PlayerController = UFWUtilities::GetFirstFWPlayerController(this);
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

bool AFWMainGameMode::IsGamePaused()
{
	return CurrentState == EGameState::Paused;
}

void AFWMainGameMode::TogglePause()
{
	SetGamePaused(!IsGamePaused());
}

bool AFWMainGameMode::IsGameWon()
{
	return CurrentState == EGameState::GameOver_Win;
}

bool AFWMainGameMode::IsGameLost()
{
	return CurrentState == EGameState::GameOver_Lose;
}

void AFWMainGameMode::SetGameWon()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Won!"));
	CurrentState = EGameState::GameOver_Win;
	OnGameWon.Broadcast();
}

void AFWMainGameMode::SetGameLost()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Lost!"));
	CurrentState = EGameState::GameOver_Lose;
	OnGameLost.Broadcast();
}

class AFWScenarioManager* AFWMainGameMode::GetScenarioManager() const
{
	return ScenarioManager;
}
