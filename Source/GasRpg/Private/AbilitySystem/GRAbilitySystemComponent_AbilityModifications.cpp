// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"


void UGRAbilitySystemComponent::GrantAbility(const FGameplayAbilityGrant& Grant)
{
    FGameplayAbilitySpec AbilitySpec(Grant.Class, Grant.Level);
    if (Grant.InputTag.IsValid())
        AbilitySpec.DynamicAbilityTags.AddTag(Grant.InputTag);
    if (Grant.ActiveOnGranted)
        GiveAbilityAndActivateOnce(AbilitySpec);
    else
        GiveAbility(AbilitySpec);
}

void UGRAbilitySystemComponent::GrantStartupAbilities(const TArray<FGameplayAbilityGrant>& Abilities)
{
    for (const FGameplayAbilityGrant& Ability : Abilities)
    {
        GrantAbility(Ability);
    }
    bStartupAbilitiesGiven = true;

    ForEachAbilityLambda([this](FGameplayAbilitySpec& AbilitySpec) {
        OnAbilitySpecChange.Broadcast(this, AbilitySpec);
    });
}

void UGRAbilitySystemComponent::SetLevelForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, int32 NewLevel)
{
    if (AbilitySpec.Level != NewLevel)
    {
        AbilitySpec.Level = NewLevel;
        UpdateStatusTagForAbilitySpec(AbilitySpec);

        ActivateAbilityIfEquippedPassive(AbilitySpec);
    }
}

void UGRAbilitySystemComponent::AddLevelForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, int32 AddLevel)
{
    SetLevelForAbilitySpec(AbilitySpec, AbilitySpec.Level + AddLevel);
}

void UGRAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(Spec);

    UpdateStatusTagForAbilitySpec(Spec);
}

void UGRAbilitySystemComponent::OnRemoveAbility(FGameplayAbilitySpec& Spec)
{
    Super::OnRemoveAbility(Spec);

    if (bStartupAbilitiesGiven)
    {
        OnAbilitySpecRemoving.Broadcast(this, Spec);
    }
}
