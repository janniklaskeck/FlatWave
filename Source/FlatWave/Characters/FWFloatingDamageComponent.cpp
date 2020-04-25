// Fill out your copyright notice in the Description page of Project Settings.

#include "FWFloatingDamageComponent.h"
#include "FWUtilities.h"
#include "FWPlayerCharacterBase.h"
#include "FWUserWidget.h"

void UFWFloatingDamageComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DestroyCounter += DeltaTime;
	if (DestroyCounter > TimeToDestroy)
	{
		DestroyComponent();
	}
	else
	{
		AActor* Player = UFWUtilities::GetPlayerCharacter(GetOwner());
		if (Player)
		{
			FVector CurrentRelativeLocation = GetRelativeTransform().GetLocation();
			FVector NewLocation = CurrentRelativeLocation + FVector(0.f, 0.f, MoveSpeed * DeltaTime);
			SetRelativeLocation(NewLocation);

			FVector OwnerLocation = GetOwner()->GetActorLocation();
			FVector PlayerLocation = Player->GetActorLocation();
			FRotator RotationTowardsPlayer = (PlayerLocation - OwnerLocation).Rotation();
			SetWorldRotation(RotationTowardsPlayer);
		}
	}
}

void UFWFloatingDamageComponent::SetDamageValue(float NewDamageValue)
{
	UFWUserWidget* UserWidget = Cast<UFWUserWidget>(GetUserWidgetObject());
	if (UserWidget)
	{
		UserWidget->SetFloatValue(NewDamageValue);
		float RandomX = FMath::RandRange(-100.f, 100.f);
		SetRelativeLocation(FVector(RandomX, 0.f, 0.f));
	}
}
