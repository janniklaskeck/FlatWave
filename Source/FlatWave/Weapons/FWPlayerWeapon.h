// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWPlayerWeapon.generated.h"

UCLASS(Blueprintable)
class FLATWAVE_API AFWPlayerWeapon : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ProjectileSpawn;
public:
	AFWPlayerWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);

	virtual void EquipWeapon();
	virtual void UnequipWeapon();

	virtual void TriggerPressed();
	virtual void TriggerReleased();

	virtual void AltTriggerPressed();
	virtual void AltTriggerReleased();

	virtual bool CanFire();
	virtual float GetSpread();

	virtual void FireProjectile();

	void ChangeAmmo(int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetCurrentAmmo();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetMaxAmmo();
	void ConsumeAmmo();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class UFWWeaponData* GetWeaponData() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetFireRateCounter();

	float GetFireRatePerSecond();

	UPROPERTY()
		class AFWPlayerCharacterBase* OwnerPlayer;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsTriggerPressed() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsAltTriggerPressed() const;
protected:

	float FireRateCounter = 0.f;
	bool bCanFireOnPressed = true;
	bool bTriggerPressed = false;
	bool bAltTriggerPressed = false;

	UPROPERTY(EditDefaultsOnly)
		class UFWWeaponData* WeaponData;
	UPROPERTY()
		int32 CurrentAmmo = 0;

	FVector GetProjectileSpawnLocation();
	UPROPERTY(EditDefaultsOnly)
		float AimAdjustmentCheckDistance = 50000.f;
	UPROPERTY(EditDefaultsOnly)
		float MinDistanceForAimAdjustments = 500.f;

	class AFWPlayerCharacterBase* GetOwnerCharacter() const;
	class AFWPlayerController* GetOwnerPlayerController() const;

	template<class T>
	T* GetWeaponDataAs() const;
};

template<class T>
T* AFWPlayerWeapon::GetWeaponDataAs() const
{
	return Cast<T>(WeaponData);
}
