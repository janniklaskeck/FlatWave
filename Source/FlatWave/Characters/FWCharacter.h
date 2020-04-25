// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FWCharacter.generated.h"

UCLASS(Abstract)
class FLATWAVE_API AFWCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFWCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
		class UFWHealthComponent* HealthComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnDeath();
public:
	class UFWHealthComponent* GetHealthComponent() const;
protected:
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
};
