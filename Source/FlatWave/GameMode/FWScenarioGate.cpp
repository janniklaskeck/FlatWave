// Fill out your copyright notice in the Description page of Project Settings.

#include "FWScenarioGate.h"
#include "FWUtilities.h"
#include "FWMainGameMode.h"
#include "FWScenarioManager.h"

void AFWScenarioGate::BeginPlay()
{
	Super::BeginPlay();
	AFWMainGameMode* GameMode = UFWUtilities::GetFWMainGameMode(this);
	if (GameMode)
		GameMode->OnGameStart.AddDynamic(this, &AFWScenarioGate::BindActions);
}

void AFWScenarioGate::BindActions()
{
	AFWMainGameMode* GameMode = UFWUtilities::GetFWMainGameMode(this);
	GameMode->GetScenarioManager()->OnStageStart.AddDynamic(this, &AFWScenarioGate::CheckForActivation);
	GameMode->GetScenarioManager()->OnStageEnd.AddDynamic(this, &AFWScenarioGate::CheckForDeactivation);
}

void AFWScenarioGate::CheckForActivation(int32 Index)
{
	if (Index == StartStageIndex)
	{
		if (bDeactivateOnStart)
		{
			Deactivate();
		}
		else
		{
			Activate();
		}
	}
}

void AFWScenarioGate::CheckForDeactivation(int32 Index)
{
	if (Index == EndStageIndex)
	{
		if (bActivateOnEnd)
		{
			Activate();
		}
		else
		{
			Deactivate();
		}
	}
}
