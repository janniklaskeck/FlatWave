// Fill out your copyright notice in the Description page of Project Settings.

#include "FWEnemySuicideBot.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FWDamgeTypeBase.h"
#include "FlatWave.h"

AFWEnemySuicideBot::AFWEnemySuicideBot()
{
	BombParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("BombParticle");
	BombParticleSystem->SetupAttachment(ChassisComponent);
	DeathParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("DeathParticle");
	DeathParticleSystem->SetupAttachment(ChassisComponent);
	DeathParticleSystem->bAutoActivate = false;
}

void AFWEnemySuicideBot::OnDeath()
{
	Super::OnDeath();
	Explode();
}

void AFWEnemySuicideBot::Explode()
{
	DeathParticleSystem->Activate();
	BombParticleSystem->SetVisibility(false, true);
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, GetActorLocation(), ExplosionRadius, UFWDamgeTypeBase::StaticClass(), IgnoredActors, this, GetController(), false, TRACE_NOCOLLISION);
	if (ExplosionSound)
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
}
