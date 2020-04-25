// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "FWPlayerController.generated.h"

UCLASS()
class FLATWAVE_API AFWPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFWPlayerController();

	void SetupInputComponent() override;

	void Tick(float DeltaSeconds);

	void Enable();
	void Disable();

private:
	void OnTriggerPressed();
	void OnTriggerReleased();

	void OnAltTriggerPressed();
	void OnAltTriggerReleased();

	void SwitchToFirstWeapon();
	void SwitchToSecondWeapon();
	void SwitchToThirdWeapon();

	void SwitchToNextWeapon();
	void SwitchToPreviousWeapon();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnYaw(float Value);
	void TurnPitch(float Value);

	void Jump();
	void StopJump();

	void DodgePressed();

	void PausePressed();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class AFWPlayerCharacterBase* GetPlayerPawn() const;
};
