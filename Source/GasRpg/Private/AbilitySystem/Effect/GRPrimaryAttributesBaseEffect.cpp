// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/GRPrimaryAttributesBaseEffect.h"
#include "AbilitySystem/GRMainAttributeSet.h"
#include "AbilitySystem/GRMainAttributeList.h"


UGRPrimaryAttributesBaseEffect::UGRPrimaryAttributesBaseEffect()
{
    DurationPolicy = EGameplayEffectDurationType::Infinite;

    FGameplayModifierInfo ModifierInfo;
    ModifierInfo.ModifierOp = EGameplayModOp::Additive;
    ModifierInfo.ModifierMagnitude = FScalableFloat();

    #define AddPrimaryAttributeModifier(AttributeName, CategoryName) \
        ModifierInfo.Attribute = UGRMainAttributeSet::Get##AttributeName##Attribute(); \
        Modifiers.Add(ModifierInfo); \

    FOREACH_ATTRIBUTE_Primary(AddPrimaryAttributeModifier);

}
