// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FWGameInstance.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API UFWGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void SetMouseSensitivityScale(float NewScale);
	UFUNCTION(BlueprintCallable)
		void IncreaseSensitivity(float Interval = 0.2f);
	UFUNCTION(BlueprintCallable)
		void DecreaseSensitivity(float Interval = -.2f);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetMouseSensitivityScale();

	UFUNCTION(BlueprintCallable)
		void SaveSettings();
	void LoadSettings();
private:
	UPROPERTY(EditDefaultsOnly)
		class USoundClass* MasterClass;
	UPROPERTY(EditDefaultsOnly)
		class USoundClass* EffectsClass;
	UPROPERTY(EditDefaultsOnly)
		class USoundClass* MusicClass;

	UPROPERTY()
		class UFWSettingsSaveGame* SettingsSaveGame;
	FString SettingsSaveGameName = FString(TEXT("SettingsSlot"));

	void Init() override;
	void Shutdown() override;
};
