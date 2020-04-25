// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/FWCharacter.h"
#include "FWEnemyCharacterBase.generated.h"

/**
 *
 */
UCLASS()
class FLATWAVE_API AFWEnemyCharacterBase : public AFWCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UFWFloatingDamageComponent> FloatingDamageClass;
protected:
	void OnDeath() override;
	UPROPERTY(EditDefaultsOnly)
		float TimeToDestroy = 3.f;
	FTimerHandle DestroyTimerHandle;
	void SimpleDestroy();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SpawnDamageWidget(float Damage);
};
