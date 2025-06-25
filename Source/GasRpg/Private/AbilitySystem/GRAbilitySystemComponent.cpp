// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "Data/GRAbilityKit.h"


/** Initialization */

void UGRAbilitySystemComponent::AbilitySystemInit(UGRAbilityKit* AdditionalKit)
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::Client_OnEffectApplied);

    UGRAbilityKit* Kit;
    if (IsValid(AdditionalKit))
    {
        AdditionalKit->Parents.Add(AbilityKit);
        Kit = AdditionalKit;
    }
    else
        Kit = AbilityKit;

    if (IsValid(Kit))
    {
        if (GetOwner() && GetOwner()->HasAuthority())
        {
            AddKitBaseEffects(Kit);
            AddKitStartupAbilities(Kit);
            ApplyKitStartupEffects(Kit);
        }
    }

    if (IsValid(AdditionalKit))
        AdditionalKit->Parents.Pop();

}

void UGRAbilitySystemComponent::AddKitBaseEffects(UGRAbilityKit* Kit)
{
    TArray<TSubclassOf<UGameplayEffect>> BaseEffects;
    Kit->GetBaseEffects(BaseEffects);

    for(const TSubclassOf<UGameplayEffect>& EffectClass : BaseEffects)
    {
        AddBaseEffect(EffectClass);
    }
}

void UGRAbilitySystemComponent::AddKitStartupAbilities(UGRAbilityKit* Kit)
{
    TArray<FGameplayAbilityGrant> StartupAbilities;
    Kit->GetStartupAbilities(StartupAbilities);

    for (const FGameplayAbilityGrant& Ability : StartupAbilities)
    {
        GrantAbility(Ability);
    }
    bStartupAbilitiesGiven = true;

    ForEachAbilityLambda([this](FGameplayAbilitySpec& AbilitySpec) {
        OnAbilitySpecChange.Broadcast(this, AbilitySpec);
    });
}

void UGRAbilitySystemComponent::ApplyKitStartupEffects(UGRAbilityKit* Kit)
{
    TArray<FGameplayEffectParameters> StartupEffects;
    Kit->GetStartupEffects(StartupEffects);
    for(const FGameplayEffectParameters& Effect : StartupEffects)
    {
        UGRAbilitySystemLibrary::ApplyGameplayEffectWithParameters(Effect, nullptr, this);
    }
}

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
