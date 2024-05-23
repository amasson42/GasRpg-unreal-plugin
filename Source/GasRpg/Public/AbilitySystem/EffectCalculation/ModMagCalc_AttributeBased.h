// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ModMagCalc_AttributeBased.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UModMagCalc_AttributeBased : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Ability|Gameplay Effect")
	void GetCapturedAttributesMagnitudes(const FGameplayEffectSpec& EffectSpec, TArray<float>& Attributes) const;

};
