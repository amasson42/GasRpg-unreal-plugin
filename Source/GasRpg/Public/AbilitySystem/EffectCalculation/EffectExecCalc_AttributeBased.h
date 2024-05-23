// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EffectExecCalc_AttributeBased.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UEffectExecCalc_AttributeBased : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Data")
	void GetCapturedAttributesMagnitudes(const FGameplayEffectCustomExecutionParameters& ExecutionParams, TArray<float>& Attributes) const;

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Data")
	void GetOwningSpec(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectSpec& OwningSpec) const;

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Data")
	float GetSetByCallerTagMagnitude(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayTag DataTag, bool WarnIfNotFound = false, float Default = 0.0f) const;

	UFUNCTION(BlueprintCallable, Category = "Ability|Gameplay Effect")
	const TMap<FGameplayTag, float>& GetSetByCallerTagMagnitudes(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Modifiers")
	void AddExecutionOutputs(const TArray<FGameplayModifierEvaluatedData>& EvaluatedDatas, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;


	/** Attribute Modifiers */

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Attribute Modifier")
	FGameplayModifierEvaluatedData MakeModifierEvaluatedData_IncomingDamage(EGameplayModOp::Type Operation, float Value) const;

};
