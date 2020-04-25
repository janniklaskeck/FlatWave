// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FWSpawner.generated.h"

UCLASS()
class FLATWAVE_API AFWSpawner : public AActor
{
	GENERATED_BODY()
public:
	AFWSpawner();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Debug, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Root;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Debug, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* VisualDebugMeshComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	virtual AActor* SpawnActor();
protected:
	virtual AActor* SpawnActorInternal(UClass* ActorClass, FVector Location, FRotator Rotation);
	virtual FVector GetSpawnLocation();
	virtual FRotator GetSpawnRotation();
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> DefaultSpawnedClass;
	UPROPERTY(EditDefaultsOnly)
		bool bSpawnOnBeginPlay = true;
};
