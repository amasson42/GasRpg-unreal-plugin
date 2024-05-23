// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


/** Initialization */

void UGRAbilitySystemComponent::AbilitySystemInitDone()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::Client_OnEffectApplied);
}


// void UGRAbilitySystemComponent::AddAttributePoints(float Count, const FGameplayTag& AttributeTag)
// {
//     FGameplayEventData Payload;
//     Payload.EventTag = AttributeTag;
//     Payload.EventMagnitude = Count;
//     UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(), AttributeTag, Payload);
// }


void UGRAbilitySystemComponent::OnRep_ActivateAbilities()
{
    Super::OnRep_ActivateAbilities();

    if (!bStartupAbilitiesGiven)
    {
        bStartupAbilitiesGiven = true;
        ForEachAbilityLambda([this](FGameplayAbilitySpec& AbilitySpec) {
            OnAbilitySpecChange.Broadcast(this, AbilitySpec);
        });
    }
}

void UGRAbilitySystemComponent::Client_OnEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);

    OnEffectAssetTags.Broadcast(TagContainer);
}

