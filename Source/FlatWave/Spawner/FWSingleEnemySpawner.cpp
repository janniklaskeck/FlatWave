// Fill out your copyright notice in the Description page of Project Settings.

#include "FWSingleEnemySpawner.h"
#include "FWCharacter.h"
#include "FWHealthComponent.h"

AActor* AFWSingleEnemySpawner::SpawnActor()
{
	AActor* SpawnedActor = Super::SpawnActor();
	if (SpawnedActor && bRespawnOnDeath)
	{
		AFWCharacter* Character = Cast<AFWCharacter>(SpawnedActor);
		if (Character)
			Character->GetHealthComponent()->OnDeath.AddDynamic(this, &AFWSingleEnemySpawner::SimpleSpawn);
	}
	return SpawnedActor;
}

void AFWSingleEnemySpawner::SimpleSpawn()
{
	SpawnActor();
}
