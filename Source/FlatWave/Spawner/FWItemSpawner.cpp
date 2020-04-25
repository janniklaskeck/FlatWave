// Fill out your copyright notice in the Description page of Project Settings.

#include "FWItemSpawner.h"
#include "FWPlayerCharacterBase.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FWHealthComponent.h"
#include "FWPlayerWeapon.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AFWItemSpawner::AFWItemSpawner()
{
	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;

	PickupCollision = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	PickupCollision->SetupAttachment(RootComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoxMesh");
	BoxMesh->SetupAttachment(BaseMesh);
	BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFWItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (PickupData)
	{
		if (bSpawnOnBeginPlay)
		{
			ActivateItem();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AFWItemSpawner::ActivateItem, SpawnInterval, false);
		}
	}
}

void AFWItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = FRotator(0.f, 30.f * DeltaTime, 0.f);
	BoxMesh->AddRelativeRotation(NewRotation);
}

void AFWItemSpawner::ActivateItem()
{
	BoxMesh->SetVisibility(true);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFWItemSpawner::DeactivateItem()
{
	BoxMesh->SetVisibility(false);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AFWItemSpawner::ActivateItem, SpawnInterval, false);
}

bool AFWItemSpawner::CanActivateItem(class AFWPlayerCharacterBase* Player)
{
	switch (PickupData->Type)
	{
	case EPickupType::HEALTH:
		return Player->GetHealthComponent()->GetHealthPercent() < 1.f;
	case EPickupType::AMMO_ALL:
		for (AFWPlayerWeapon* Weapon : Player->GetWeapons())
		{
			if (Weapon->GetCurrentAmmo() < Weapon->GetMaxAmmo())
			{
				return true;
			}
		}
		return false;
	default:
		return true;
	}
}

void AFWItemSpawner::ApplyItem(class AFWPlayerCharacterBase* Player)
{
	switch (PickupData->Type)
	{
	case EPickupType::HEALTH:
		Player->GetHealthComponent()->ChangeHealth(PickupData->Amount);
		break;
	case EPickupType::AMMO_ALL:
		for (AFWPlayerWeapon* Weapon : Player->GetWeapons())
		{
			Weapon->ChangeAmmo(PickupData->Amount);
		}
		break;
	default:
		break;
	}
	if (PickupSound)
	{
		UGameplayStatics::PlaySound2D(this, PickupSound);
	}
}

void AFWItemSpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFWPlayerCharacterBase* Player = Cast<AFWPlayerCharacterBase>(OtherActor);
	if (Player && CanActivateItem(Player))
	{
		ApplyItem(Player);
		DeactivateItem();
	}
}
