// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/DamageType.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "FWUtilities.generated.h"

UCLASS()
class FLATWAVE_API UFWUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class AFWMainGameMode* GetFWMainGameMode(UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class UFWGameInstance* GetFWGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class AFWPlayerController* GetFWPlayerController(UObject* WorldContextObject, int32 Index);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class AFWPlayerController* GetFirstFWPlayerController(UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static class AFWPlayerCharacterBase* GetPlayerCharacter(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
		static void ApplyDamage(class AActor* DamagedActor, float Damage, class AController* InstigatorController, class AActor* DamageCauseer, TSubclassOf<class UDamageType> DamageType);
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
		static void ApplyRadialImpulse(UObject* WorldContextObject, FVector ImpulseOrigin, float ImpulseRadius, float ImpulseStrength);

	UFUNCTION(BlueprintCallable)
		static void ChangeVolume(class USoundClass* SoundClass, float NewVolume);

	template<typename T>
	static FORCEINLINE void ShuffleArray(TArray<T>& Array);
};

template<typename T>
void UFWUtilities::ShuffleArray(TArray<T>& Array)
{
	for (int32 Index = Array.Num() - 1; Index > 0; Index--)
	{
		int32 RandomIndex = FMath::RandRange(0, Index);
		Array.Swap(Index, RandomIndex);
	}
}
