// Fill out your copyright notice in the Description page of Project Settings.

#include "FWHealthComponent.h"
#include "Net/UnrealNetwork.h"

UFWHealthComponent::UFWHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bReplicates = true;
}

void UFWHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float UFWHealthComponent::GetHealth()
{
	return CurrentHealth;
}

float UFWHealthComponent::GetHealthPercent()
{
	return (float)CurrentHealth / MaxHealth;
}

float UFWHealthComponent::ChangeHealth(float Amount)
{
	if (bIsInvincible)
	{
		return Amount;
	}
	float HealthBefore = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
	if (CurrentHealth >= MaxHealth)
	{
		OnFullHealth.Broadcast();
	}
	else if (CurrentHealth <= 0.f && HealthBefore > 0.f)
	{
		OnDeath.Broadcast();
	}
	return CurrentHealth - HealthBefore;
}

void UFWHealthComponent::Reset()
{
	ChangeHealth(MaxHealth);
}
