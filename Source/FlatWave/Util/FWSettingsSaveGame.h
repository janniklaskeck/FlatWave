// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FWSettingsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		float MasterVolume = .5f;
	UPROPERTY(EditDefaultsOnly)
		float EffectsVolume = .5f;
	UPROPERTY(EditDefaultsOnly)
		float MusicVolume = .5f;

	UPROPERTY(EditDefaultsOnly)
		float MouseSensitivity = 1.f;
};
