// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GRAbilityKit.h"
#include "AbilitySystem/Effect/GRPrimaryAttributesBaseEffect.h"
#include "AbilitySystem/Effect/GRSecondaryAttributesBaseEffect.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"

void UGRAbilityKit::GetBaseEffects(TArray<TSubclassOf<UGameplayEffect>> &Effects) const
{
    TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> OverridedEffects;
    GetBaseEffects(OverridedEffects, Effects);

    for (const auto& Effect : OverridedEffects)
    {
        TSubclassOf<UGameplayEffect> Value = Effect.Value;
        Effects.Add(Value);
    }
}

void UGRAbilityKit::GetStartupAbilities(TArray<FGameplayAbilityGrant> &Abilities) const
{
    for (const TObjectPtr<UGRAbilityKit> &Parent : Parents)
    {
        if (!IsValid(Parent))
            continue;

        Parent->GetStartupAbilities(Abilities);
    }

    Abilities.Append(StartupAbilities);
}

void UGRAbilityKit::GetStartupEffects(TArray<FGameplayEffectParameters> &Effects) const
{
    for (const TObjectPtr<UGRAbilityKit>& Parent : Parents)
    {
        if (!IsValid(Parent))
            continue;

        Parent->GetStartupEffects(Effects);
    }

    Effects.Append(OnBeginEffects);
}

void UGRAbilityKit::GetBaseEffects(TMap<FGameplayTag, TSubclassOf<UGameplayEffect>>& OverridableEffects, TArray<TSubclassOf<UGameplayEffect>> &Effects) const
{
    for (const TObjectPtr<UGRAbilityKit>& Parent : Parents)
    {
        if (!IsValid(Parent))
            continue;

        Parent->GetBaseEffects(OverridableEffects, Effects);
    }

    for (const auto& Effect : OverridableBaseEffects)
        OverridableEffects.Add(Effect.Key, Effect.Value);

    for (const auto& Effect : BaseEffects)
        Effects.Add(Effect);
}
