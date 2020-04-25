// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWPickupItemData.h"
#include "FWItemSpawner.generated.h"

UCLASS()
class FLATWAVE_API AFWItemSpawner : public AActor
{
	GENERATED_BODY()
public:
	AFWItemSpawner();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* PickupCollision;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Debug, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BaseMesh;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Debug, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BoxMesh;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float SpawnInterval = 30.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bSpawnOnBeginPlay = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UFWPickupItemData* PickupData;
	UPROPERTY(EditDefaultsOnly)
		class USoundBase* PickupSound;

private:
	FTimerHandle RespawnTimerHandle;

	void ActivateItem();
	void DeactivateItem();

	bool CanActivateItem(class AFWPlayerCharacterBase* Player);

	void ApplyItem(class AFWPlayerCharacterBase* Player);

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
