// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/FWCharacter.h"
#include "FWWeaponData.h"
#include "FWDelegates.h"
#include "FWPlayerCharacterBase.generated.h"

UCLASS()
class FLATWAVE_API AFWPlayerCharacterBase : public AFWCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* LaserRifleChildActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* MinigunChildActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* RocketLauncherChildActor;
public:
	AFWPlayerCharacterBase();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	bool bIsDying = false;
	FRotator PreDeathRotation;
	float DyingCounter = 0.f;
	UPROPERTY(EditDefaultsOnly)
		float TimeToDeath = 1.5f;

	UPROPERTY(EditDefaultsOnly)
		float DodgeVerticalPart = 0.1f;
	UPROPERTY(EditDefaultsOnly)
		float DodgeVelocity = 1000.f;
	bool bCanDodge = true;
	void Landed(const FHitResult& Hit);


	UPROPERTY()
		class AFWPlayerWeapon* CurrentWeapon;
	int32 CurrentWeaponIndex;
	UPROPERTY()
		TArray<class AFWPlayerWeapon*> WeaponList;
public:
	void EquipWeapon(int32 Index);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetCurrentWeaponIndex() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		class AFWPlayerWeapon* GetWeaponAt(int32 Index) const;
	TArray<class AFWPlayerWeapon*> GetWeapons() const;
protected:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(BlueprintAssignable)
		FOnAction OnDamageTaken;

	UPROPERTY(EditDefaultsOnly, Category = Audio)
		class USoundBase* JumpSound;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
		class USoundBase* FootStepSound;
	UPROPERTY(EditDefaultsOnly)
		float FootStepInterval = .5f;
	float FootStepCounter;

	void OnDeath() override;
public:
	UFUNCTION(BlueprintCallable)
		class AFWPlayerWeapon* GetCurrentWeapon() const;

	FRotator GetProjectileSpawnRotation();

	void OnTriggerPressed();
	void OnTriggerReleased();

	void OnAltTriggerPressed();
	void OnAltTriggerReleased();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void JumpPressed();
	void JumpReleased();

	void DodgePressed();

public:
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const
	{
		return FirstPersonCameraComponent;
	}
};
