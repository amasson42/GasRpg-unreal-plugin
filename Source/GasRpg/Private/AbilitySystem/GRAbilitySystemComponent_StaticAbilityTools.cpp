// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "GasRpgGameplayTags.h"


bool UGRAbilitySystemComponent::AbilityHasIDTag(const UGameplayAbility* Ability)
{
    if (Ability)
        return Ability->AbilityTags.HasTag(FGRGameplayTags::Get().Ability_ID);
    return false;
}

FGameplayTag UGRAbilitySystemComponent::GetAbilityIDTagFromAbility(const UGameplayAbility* Ability)
{
    if (Ability)
        return UGRAbilitySystemLibrary::GetFirstMatchingTagFromTagContainer(Ability->AbilityTags, FGRGameplayTags::Get().Ability_ID);
    return FGameplayTag::EmptyTag;
}

bool UGRAbilitySystemComponent::AbilitySpecHasInputTag(const FGameplayAbilitySpec& AbilitySpec)
{
    return AbilitySpec.DynamicAbilityTags.HasTag(FGRGameplayTags::Get().InputTag);
}

FGameplayTag UGRAbilitySystemComponent::GetInputTagFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec)
{
    return UGRAbilitySystemLibrary::GetFirstMatchingTagFromTagContainer(AbilitySpec.DynamicAbilityTags, FGRGameplayTags::Get().InputTag);
}

bool UGRAbilitySystemComponent::AbilityHasCooldownTag(const UGameplayAbility* Ability)
{
    if (Ability)
        return Ability->AbilityTags.HasTag(FGRGameplayTags::Get().Ability_Cooldown);
    return false;
}

FGameplayTag UGRAbilitySystemComponent::GetCooldownTagFromAbility(const UGameplayAbility* Ability)
{
    if (Ability)
    {
        if (const FGameplayTagContainer* CooldownTags = Ability->GetCooldownTags())
        {
            return UGRAbilitySystemLibrary::GetFirstMatchingTagFromTagContainer(*CooldownTags, FGRGameplayTags::Get().Ability_Cooldown);
        }
    }
    return FGameplayTag::EmptyTag;
}

bool UGRAbilitySystemComponent::AbilitySpecHasStatusTag(const FGameplayAbilitySpec& AbilitySpec)
{
    return AbilitySpec.DynamicAbilityTags.HasTag(FGRGameplayTags::Get().Ability_Status);
}

FGameplayTag UGRAbilitySystemComponent::GetStatusTagFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec)
{
    return UGRAbilitySystemLibrary::GetFirstMatchingTagFromTagContainer(AbilitySpec.DynamicAbilityTags, FGRGameplayTags::Get().Ability_Status);
}

bool UGRAbilitySystemComponent::AbilityHasTypeTag(const UGameplayAbility* Ability)
{
    if (Ability)
        return Ability->AbilityTags.HasTag(FGRGameplayTags::Get().Ability_Type);
    return false;
}

FGameplayTag UGRAbilitySystemComponent::GetTypeTagFromAbility(const UGameplayAbility* Ability)
{
    if (Ability)
    {
        return UGRAbilitySystemLibrary::GetFirstMatchingTagFromTagContainer(Ability->AbilityTags, FGRGameplayTags::Get().Ability_Type);
    }
    return FGameplayTag::EmptyTag;
}
