// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define COLLISION_PROJECTILE ECollisionChannel::ECC_GameTraceChannel1
#define TRACE_NOCOLLISION ECollisionChannel::ECC_GameTraceChannel2

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?"))
