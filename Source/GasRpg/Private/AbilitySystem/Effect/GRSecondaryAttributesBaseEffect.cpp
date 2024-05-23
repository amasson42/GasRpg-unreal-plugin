// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effect/GRSecondaryAttributesBaseEffect.h"
#include "AbilitySystem/GRMainAttributeSet.h"
#include "AbilitySystem/GRMainAttributeList.h"


UGRSecondaryAttributesBaseEffect::UGRSecondaryAttributesBaseEffect()
{
    DurationPolicy = EGameplayEffectDurationType::Infinite;

    FGameplayModifierInfo ModifierInfo;
    ModifierInfo.ModifierOp = EGameplayModOp::Additive;
    ModifierInfo.ModifierMagnitude = FAttributeBasedFloat();

    #define AddSecondaryAttributeModifier(AttributeName, CategoryName) \
        ModifierInfo.Attribute = UGRMainAttributeSet::Get##AttributeName##Attribute(); \
        Modifiers.Add(ModifierInfo); \

    #define AddVitalMaxAttributeModifier(VitalAttr, CategoryName) \
        AddSecondaryAttributeModifier(Max##VitalAttr, CategoryName)

    FOREACH_ATTRIBUTE_Vital_NoMax(AddVitalMaxAttributeModifier);

    FOREACH_ATTRIBUTE_Secondary(AddSecondaryAttributeModifier);

}
