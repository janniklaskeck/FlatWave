// Fill out your copyright notice in the Description page of Project Settings.

#include "FWUtilities.h"
#include "FWMainGameMode.h"
#include "FWPlayerController.h"
#include "FWPlayerCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "Sound/SoundClass.h"
#include "FWGameInstance.h"

class AFWMainGameMode* UFWUtilities::GetFWMainGameMode(UObject* WorldContextObject)
{
	return Cast<AFWMainGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

class UFWGameInstance* UFWUtilities::GetFWGameInstance(UObject* WorldContextObject)
{
	return Cast<UFWGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

class AFWPlayerController* UFWUtilities::GetFWPlayerController(UObject* WorldContextObject, int32 Index)
{
	return Cast<AFWPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, Index));
}

class AFWPlayerController* UFWUtilities::GetFirstFWPlayerController(UObject* WorldContextObject)
{
	return GetFWPlayerController(WorldContextObject, 0);
}

class AFWPlayerCharacterBase* UFWUtilities::GetPlayerCharacter(UObject* WorldContextObject)
{
	AFWPlayerController* Controller = GetFirstFWPlayerController(WorldContextObject);
	if (Controller)
		return Cast<AFWPlayerCharacterBase>(Controller->GetPawn());
	return nullptr;
}

void UFWUtilities::ApplyDamage(class AActor* DamagedActor, float Damage, class AController* InstigatorController, class AActor* DamageCauseer, TSubclassOf<class UDamageType> DamageType)
{
	UGameplayStatics::ApplyDamage(DamagedActor, Damage, InstigatorController, DamageCauseer, DamageType);
}

void UFWUtilities::ApplyRadialImpulse(UObject* WorldContextObject, FVector ImpulseOrigin, float ImpulseRadius, float ImpulseStrength)
{
	check(WorldContextObject);
	UWorld* World = WorldContextObject->GetWorld();
	TArray<FOverlapResult> Overlaps;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ImpulseRadius);
	if (World->OverlapMultiByObjectType(Overlaps, ImpulseOrigin, FQuat::Identity, ObjectQueryParams, CollisionShape))
	{
		TArray<UPrimitiveComponent*, TInlineAllocator<1>> AffectedComponents;
		AffectedComponents.Reserve(Overlaps.Num());

		for (FOverlapResult& OverlapResult : Overlaps)
		{
			if (UPrimitiveComponent* PrimitiveComponent = OverlapResult.Component.Get())
			{
				AffectedComponents.AddUnique(PrimitiveComponent);
			}
		}

		for (UPrimitiveComponent* PrimitiveComponent : AffectedComponents)
		{
			PrimitiveComponent->AddRadialForce(ImpulseOrigin, ImpulseRadius, ImpulseStrength, ERadialImpulseFalloff::RIF_Linear);
		}
	}
}

void UFWUtilities::ChangeVolume(class USoundClass* SoundClass, float NewVolume)
{
	if (SoundClass)
	{
		SoundClass->Properties.Volume = FMath::Clamp(NewVolume, 0.f, 1.f);
	}
}
