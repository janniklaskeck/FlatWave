// Fill out your copyright notice in the Description page of Project Settings.

#include "FWCharacter.h"
#include "FWHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFWCharacter, Warning, All);

AFWCharacter::AFWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UFWHealthComponent>("HealthComponent");
}

void AFWCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddDynamic(this, &AFWCharacter::OnDeath);
}

void AFWCharacter::OnDeath()
{
	Destroy();
}

class UFWHealthComponent* AFWCharacter::GetHealthComponent() const
{
	return HealthComponent;
}

void AFWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFWCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = 0.f;
	if (HealthComponent->GetHealth() > 0.f)
	{
		ActualDamage = HealthComponent->ChangeHealth(-DamageAmount);
	}
	return ActualDamage;
}

