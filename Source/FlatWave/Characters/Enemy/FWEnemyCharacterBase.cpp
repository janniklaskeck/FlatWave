// Fill out your copyright notice in the Description page of Project Settings.

#include "FWEnemyCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "FWAIController.h"
#include "TimerManager.h"
#include "FWFloatingDamageComponent.h"

void AFWEnemyCharacterBase::OnDeath()
{
	if (GetController())
		GetController()->UnPossess();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AFWEnemyCharacterBase::SimpleDestroy, 1.f, false, TimeToDestroy);
}

void AFWEnemyCharacterBase::SimpleDestroy()
{
	Destroy();
}

float AFWEnemyCharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser->Instigator != this && !Cast<AFWAIController>(EventInstigator))
	{
		float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		if (FMath::Abs(ActualDamage) > 0.f)
		{
			SpawnDamageWidget(ActualDamage);
		}
		return ActualDamage;
	}
	return 0.f;
}

void AFWEnemyCharacterBase::SpawnDamageWidget(float Damage)
{
	UFWFloatingDamageComponent* FloatingDamage = NewObject<UFWFloatingDamageComponent>(this, FloatingDamageClass);
	FloatingDamage->RegisterComponent();
	FloatingDamage->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	FloatingDamage->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	FloatingDamage->SetDamageValue(FMath::Abs(Damage));
}
