// Fill out your copyright notice in the Description page of Project Settings.

#include "FWGameInstance.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"
#include "FWSettingsSaveGame.h"

void UFWGameInstance::SetMouseSensitivityScale(float NewScale)
{
	SettingsSaveGame->MouseSensitivity = NewScale;
}

void UFWGameInstance::IncreaseSensitivity(float Interval /*= 0.2f*/)
{
	SettingsSaveGame->MouseSensitivity = FMath::Clamp(SettingsSaveGame->MouseSensitivity + Interval, 0.2f, 2.f);
}

void UFWGameInstance::DecreaseSensitivity(float Interval /*= -.2f*/)
{
	SettingsSaveGame->MouseSensitivity = FMath::Clamp(SettingsSaveGame->MouseSensitivity + Interval, 0.2f, 2.f);
}

float UFWGameInstance::GetMouseSensitivityScale()
{
	return SettingsSaveGame->MouseSensitivity;
}

void UFWGameInstance::SaveSettings()
{
	if (!SettingsSaveGame)
	{
		SettingsSaveGame = Cast<UFWSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(UFWSettingsSaveGame::StaticClass()));
	}
	if (MasterClass)
		SettingsSaveGame->MasterVolume = MasterClass->Properties.Volume;
	if (EffectsClass)
		SettingsSaveGame->EffectsVolume = EffectsClass->Properties.Volume;
	if (MusicClass)
		SettingsSaveGame->MusicVolume = MusicClass->Properties.Volume;
	UGameplayStatics::SaveGameToSlot(SettingsSaveGame, SettingsSaveGameName, 0);
}

void UFWGameInstance::LoadSettings()
{
	USaveGame* LoadedSave = UGameplayStatics::LoadGameFromSlot(SettingsSaveGameName, 0);
	if (LoadedSave)
	{
		SettingsSaveGame = Cast<UFWSettingsSaveGame>(LoadedSave);
		if (MasterClass)
			MasterClass->Properties.Volume = SettingsSaveGame->MasterVolume;
		if (EffectsClass)
			EffectsClass->Properties.Volume = SettingsSaveGame->EffectsVolume;
		if (MusicClass)
			MusicClass->Properties.Volume = SettingsSaveGame->MusicVolume;
	}
	else
	{
		SaveSettings();
	}
}

void UFWGameInstance::Init()
{
	Super::Init();
	LoadSettings();
}

void UFWGameInstance::Shutdown()
{
	Super::Shutdown();
	SaveSettings();
}
