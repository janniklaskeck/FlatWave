// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWProjectile.generated.h"

UCLASS()
class FLATWAVE_API AFWProjectile : public AActor
{
	GENERATED_BODY()
public:
	AFWProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class UAudioComponent* MovementSoundComponent;

	void Destroyed() override;

	void DestroyProjectile();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
public:
	UPROPERTY(EditDefaultsOnly)
		class UFWProjectileData* ProjectileData;

	void SetInitialVelocity(float Velocity);

	class UProjectileMovementComponent* GetProjectileMovement() const;

	void NotifyActorBeginOverlap(AActor* OtherActor);
};
