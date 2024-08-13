// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "GasRpgGameplayTags.h"


void UGRAbilitySystemComponent::ForEachAbilityDelegate(const FForEachAbilityDelegate& Delegate)
{
    FScopedAbilityListLock ActiveScopeLock(*this);
    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        Delegate.ExecuteIfBound(AbilitySpec);
    }
}

void UGRAbilitySystemComponent::ForEachAbilityLambda(TFunction<void (FGameplayAbilitySpec&)> Func)
{
    FScopedAbilityListLock ActiveScopeLock(*this);
    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        Func(AbilitySpec);
    }
}

FGameplayAbilitySpec* UGRAbilitySystemComponent::GetAbilitySpecForAbilityIDTag(const FGameplayTag& AbilityIDTag)
{
    FScopedAbilityListLock ActiveScopeLock(*this);
    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (UGRAbilitySystemComponent::GetAbilityIDTagFromAbility(AbilitySpec.Ability).MatchesTag(AbilityIDTag))
        {
            return &AbilitySpec;
        }
    }
    return nullptr;
}

void UGRAbilitySystemComponent::GetAbilitySpecsForInputTag(const FGameplayTag& InputTag, TArray<FGameplayAbilitySpec*>& AbilitySpecs)
{
    FScopedAbilityListLock ActiveScopeLock(*this);
    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.DynamicAbilityTags.HasTag(InputTag))
        {
            AbilitySpecs.Add(&AbilitySpec);
        }
    }
}

bool UGRAbilitySystemComponent::GetStatusTagForAbilityIDTag(const FGameplayTag AbilityIDTag, FGameplayTag& StatusTag)
{
    if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecForAbilityIDTag(AbilityIDTag))
    {
        FGameplayTag SpecStatusTag = GetStatusTagFromAbilitySpec(*AbilitySpec);
        if (SpecStatusTag.IsValid())
        {
            StatusTag = SpecStatusTag;
            return true;
        }
    }
    return false;
}

void UGRAbilitySystemComponent::RemoveInputTagFromAbilitySpec(FGameplayAbilitySpec& AbilitySpec, bool bBroadcastUpdate)
{
    if (UGRAbilitySystemLibrary::RemoveMatchingTagsFromTagContainer(AbilitySpec.DynamicAbilityTags, FGRGameplayTags::Get().InputTag))
    {
        if (AbilitySpec.IsActive())
            CancelAbilityHandle(AbilitySpec.Handle);

        UpdateStatusTagForAbilitySpec(AbilitySpec, bBroadcastUpdate);
    }
}

void UGRAbilitySystemComponent::ClearAbilitiesFromInputTag(const FGameplayTag& InputTag)
{
    TArray<FGameplayAbilitySpec*> AbilitySpecs;
    GetAbilitySpecsForInputTag(InputTag, AbilitySpecs);

    for (FGameplayAbilitySpec* AbilitySpec : AbilitySpecs)
    {
        RemoveInputTagFromAbilitySpec(*AbilitySpec);
    }
}

void UGRAbilitySystemComponent::AssignInputTagToAbilitySpec(const FGameplayTag& InputTag, FGameplayAbilitySpec& AbilitySpec)
{
    RemoveInputTagFromAbilitySpec(AbilitySpec, false);

    ClearAbilitiesFromInputTag(InputTag);

    AbilitySpec.DynamicAbilityTags.AddTag(InputTag);

    UpdateStatusTagForAbilitySpec(AbilitySpec, true);

    ActivateAbilityIfEquippedPassive(AbilitySpec);
}


void UGRAbilitySystemComponent::UpdateStatusTagForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, bool bBroadcastUpdate)
{
    FGameplayTag StatusTag;
    if (AbilitySpec.DynamicAbilityTags.HasTag(FGRGameplayTags::Get().InputTag))
        StatusTag = FGRGameplayTags::Get().Ability_Status_Equipped;
    else if (AbilitySpec.Level > 0)
        StatusTag = FGRGameplayTags::Get().Ability_Status_Unlocked;
    else
        StatusTag = FGRGameplayTags::Get().Ability_Status_Eligible;

    SetStatusTagForAbilitySpec(AbilitySpec, StatusTag, bBroadcastUpdate);

    if (bBroadcastUpdate)
    {
        const FGameplayTag& AbilityID = GetAbilityIDTagFromAbility(AbilitySpec.Ability);
        Client_UpdateAbilityStatus(AbilityID, StatusTag, AbilitySpec.Level);
    }
}

void UGRAbilitySystemComponent::SetStatusTagForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& StatusTag, bool bBroadcastUpdate)
{
    UGRAbilitySystemLibrary::RemoveMatchingTagsFromTagContainer(AbilitySpec.DynamicAbilityTags, FGRGameplayTags::Get().Ability_Status);
    AbilitySpec.DynamicAbilityTags.AddTag(StatusTag);
    MarkAbilitySpecDirty(AbilitySpec);

    if (bBroadcastUpdate && bStartupAbilitiesGiven)
        OnAbilitySpecChange.Broadcast(this, AbilitySpec);
}

void UGRAbilitySystemComponent::Client_UpdateAbilityStatus_Implementation(const FGameplayTag& AbilityID, const FGameplayTag& Status, int32 Level)
{
    FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecForAbilityIDTag(AbilityID);
    if (!AbilitySpec) return;

    AbilitySpec->Level = Level;
    SetStatusTagForAbilitySpec(*AbilitySpec, Status);
}