// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/Actor.h"
#include "FWDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAction);


UCLASS()
class FLATWAVE_API AFWDelegates : public AActor
{
	GENERATED_BODY()
};