// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GRCharacterKit.h"
#include "AbilitySystem/Effect/GRPrimaryAttributesBaseEffect.h"
#include "AbilitySystem/Effect/GRSecondaryAttributesBaseEffect.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"

TSubclassOf<UGameplayEffect> UGRCharacterKit::GetPrimaryAttributesEffects() const
{
    if (IsValid(PrimaryAttributesEffect))
        return PrimaryAttributesEffect;

    for (int32 i = Parents.Num() - 1; i >= 0; --i)
    {
        const TObjectPtr<UGRCharacterKit> &Parent = Parents[i];
        if (!IsValid(Parent))
            continue;

        TSubclassOf<UGameplayEffect> Effect = Parent->GetPrimaryAttributesEffects();
        if (IsValid(Effect))
            return Effect;
    }

    return nullptr;
}

TSubclassOf<UGameplayEffect> UGRCharacterKit::GetSecondaryAttributesEffects() const
{
    if (IsValid(SecondaryAttributesEffect))
        return SecondaryAttributesEffect;

    for (int32 i = Parents.Num() - 1; i >= 0; --i)
    {
        const TObjectPtr<UGRCharacterKit> &Parent = Parents[i];
        if (!IsValid(Parent))
            continue;

        TSubclassOf<UGameplayEffect> Effect = Parent->GetSecondaryAttributesEffects();
        if (IsValid(Effect))
            return Effect;
    }

    return nullptr;
}

void UGRCharacterKit::GetBaseEffects(TArray<TSubclassOf<UGameplayEffect>> &Effects, bool bIncludeAttributes) const
{
    if (bIncludeAttributes)
    {
        TSubclassOf<UGameplayEffect> PrimaryEffect = GetPrimaryAttributesEffects();
        if (IsValid(PrimaryEffect))
            Effects.Add(PrimaryEffect);

        TSubclassOf<UGameplayEffect> SecondaryEffect = GetSecondaryAttributesEffects();
        if (IsValid(SecondaryEffect))
            Effects.Add(SecondaryEffect);
    }

    for (const TObjectPtr<UGRCharacterKit> &Parent : Parents)
    {
        if (!IsValid(Parent))
            continue;

        Parent->GetBaseEffects(Effects, false);
    }

    Effects.Append(BaseEffects);
}

void UGRCharacterKit::GetStartupAbilities(TArray<FGameplayAbilityGrant> &Abilities) const
{
    for (const TObjectPtr<UGRCharacterKit> &Parent : Parents)
    {
        if (!IsValid(Parent))
            continue;

        Parent->GetStartupAbilities(Abilities);
    }

    Abilities.Append(StartupAbilities);
}

void UGRCharacterKit::GetOnBeginEffects(TArray<FGameplayEffectParameters> &Effects) const
{
    for (const TObjectPtr<UGRCharacterKit> &Parent : Parents)
    {
        if (!IsValid(Parent))
            continue;

        Parent->GetOnBeginEffects(Effects);
    }

    Effects.Append(OnBeginEffects);
}

void UGRCharacterKit::GetStartupAbilitiesForInputs(TMap<FGameplayTag, FGameplayTag> &AbilitiesForInputs) const
{
    TArray<FGameplayAbilityGrant> GrantedAbilities;
    GetStartupAbilities(GrantedAbilities);

    for (const FGameplayAbilityGrant &GrantedAbility : GrantedAbilities)
    {
        UGameplayAbility *Ability = GrantedAbility.Class.GetDefaultObject();
        FGameplayTag AbilityID = UGRAbilitySystemComponent::GetAbilityIDTagFromAbility(Ability);
        if (GrantedAbility.InputTag.IsValid())
        {
            AbilitiesForInputs.Add(GrantedAbility.InputTag, AbilityID);
        }
    }
}
