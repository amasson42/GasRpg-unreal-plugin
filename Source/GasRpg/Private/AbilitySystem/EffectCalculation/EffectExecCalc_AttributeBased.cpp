// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EffectCalculation/EffectExecCalc_AttributeBased.h"
#include "AbilitySystem/GRVitalAttributeSet.h"


void UEffectExecCalc_AttributeBased::GetCapturedAttributesMagnitudes(const FGameplayEffectCustomExecutionParameters& ExecutionParams, TArray<float>& Attributes) const
{
    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    const FGameplayTagContainer* SourceTag = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTag = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTag;
    EvaluationParameters.TargetTags = TargetTag;

    for (FGameplayEffectAttributeCaptureDefinition AttributeCaptureDefinition : RelevantAttributesToCapture)
    {
        float AttributeValue = 0.0f;
        ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttributeCaptureDefinition, EvaluationParameters, AttributeValue);
        Attributes.Add(AttributeValue);
    }
}

void UEffectExecCalc_AttributeBased::GetOwningSpec(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectSpec& OwningSpec) const
{
    OwningSpec = ExecutionParams.GetOwningSpec();
}

float UEffectExecCalc_AttributeBased::GetSetByCallerTagMagnitude(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayTag DataTag, bool WarnIfNotFound, float Default) const
{
    return ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(DataTag, WarnIfNotFound, Default);
}

const TMap<FGameplayTag, float>& UEffectExecCalc_AttributeBased::GetSetByCallerTagMagnitudes(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
    return ExecutionParams.GetOwningSpec().SetByCallerTagMagnitudes;
}

void UEffectExecCalc_AttributeBased::AddExecutionOutputs(const TArray<FGameplayModifierEvaluatedData>& EvaluatedDatas, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    for (const FGameplayModifierEvaluatedData& EvaluatedData : EvaluatedDatas)
    {
        OutExecutionOutput.AddOutputModifier(EvaluatedData);
    }
}


/** Attribute Modifiers */

FGameplayModifierEvaluatedData UEffectExecCalc_AttributeBased::MakeModifierEvaluatedData_IncomingDamage(EGameplayModOp::Type Operation, float Value) const
{
    return FGameplayModifierEvaluatedData(UGRVitalAttributeSet::GetIncomingDamageAttribute(), Operation, Value);
}
