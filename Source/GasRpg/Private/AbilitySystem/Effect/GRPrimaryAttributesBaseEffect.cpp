// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/GRPrimaryAttributesBaseEffect.h"
#include "AbilitySystem/GRVitalAttributeSet.h"


UGRPrimaryAttributesBaseEffect::UGRPrimaryAttributesBaseEffect()
{
    DurationPolicy = EGameplayEffectDurationType::Infinite;

    FGameplayModifierInfo ModifierInfo;
    ModifierInfo.ModifierOp = EGameplayModOp::Additive;
    ModifierInfo.ModifierMagnitude = FScalableFloat();

}
