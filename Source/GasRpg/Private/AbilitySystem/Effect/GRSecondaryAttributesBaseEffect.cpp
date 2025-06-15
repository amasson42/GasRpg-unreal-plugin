// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/GRSecondaryAttributesBaseEffect.h"
#include "AbilitySystem/GRVitalAttributeSet.h"


UGRSecondaryAttributesBaseEffect::UGRSecondaryAttributesBaseEffect()
{
    DurationPolicy = EGameplayEffectDurationType::Infinite;

    FGameplayModifierInfo ModifierInfo;
    ModifierInfo.ModifierOp = EGameplayModOp::Additive;
    ModifierInfo.ModifierMagnitude = FAttributeBasedFloat();

    ModifierInfo.Attribute = UGRVitalAttributeSet::GetMaxHealthAttribute();
    Modifiers.Add(ModifierInfo);

}
