// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EffectCalculation/ModMagCalc_AttributeBased.h"


void UModMagCalc_AttributeBased::GetCapturedAttributesMagnitudes(const FGameplayEffectSpec& EffectSpec, TArray<float>& Attributes) const
{
    const FGameplayTagContainer* SourceTag = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTag = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTag;
    EvaluationParameters.TargetTags = TargetTag;

    for (FGameplayEffectAttributeCaptureDefinition AttributeCaptureDefinition : RelevantAttributesToCapture)
    {
        float AttributeValue = 0.0f;
        GetCapturedAttributeMagnitude(AttributeCaptureDefinition, EffectSpec, EvaluationParameters, AttributeValue);
        Attributes.Add(AttributeValue);
    }
}
