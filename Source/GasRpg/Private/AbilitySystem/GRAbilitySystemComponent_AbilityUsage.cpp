// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "GasRpgGameplayTags.h"

// TODO: Make a map of TMap<FGameplayTag, FGameplayAbilitySpec*> so we find the ability spec matching the input faster. updated when we modify an ability spec.

void UGRAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid())
        return;

    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
        {
            AbilitySpecInputPressed(AbilitySpec);
            if (AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
        }
    }
}

void UGRAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid())
        return;

    if (HasMatchingGameplayTag(FGRGameplayTags::Get().Player_UI_Disable_AbilityInputs))
        return;

    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
        {
            if (!AbilitySpec.IsActive())
            {
                AbilitySpecInputPressed(AbilitySpec);
                TryActivateAbility(AbilitySpec.Handle);
            }
        }
    }
}

void UGRAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid())
        return;

    for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
        {
            AbilitySpecInputReleased(AbilitySpec);
            if (AbilitySpec.IsActive())
            {
                InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
            }
        }
    }
}

void UGRAbilitySystemComponent::ActivateAbilityIfEquippedPassive(FGameplayAbilitySpec& AbilitySpec)
{
    bool bIsEquipped = GetStatusTagFromAbilitySpec(AbilitySpec).MatchesTagExact(FGRGameplayTags::Get().Ability_Status_Equipped);
    if (!bIsEquipped) return;

    const FGameplayTag AbilityType = GetTypeTagFromAbility(AbilitySpec.Ability);
    const bool bIsPassiveAbility = AbilityType.MatchesTagExact(FGRGameplayTags::Get().Ability_Type_Passive);
    if (!bIsPassiveAbility) return;

    TryActivateAbility(AbilitySpec.Handle);
}
