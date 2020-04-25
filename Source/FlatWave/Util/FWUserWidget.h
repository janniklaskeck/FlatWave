// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FWUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLATWAVE_API UFWUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetFloatValue(float NewValue);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetFloatValue();
private:
	float FloatValue;
};
