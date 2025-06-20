// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "Data/GRAbilityKit.h"


/** Initialization */

void UGRAbilitySystemComponent::AbilitySystemInitDone()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::Client_OnEffectApplied);

    if (GetOwner() && GetOwner()->HasAuthority() && IsValid(AbilityKit))
    {
        AddKitBaseEffects();
        AddKitStartupAbilities();
        ApplyKitStartupEffects();
    }
}

void UGRAbilitySystemComponent::AddKitBaseEffects()
{
    TArray<TSubclassOf<UGameplayEffect>> BaseEffects;
    AbilityKit->GetBaseEffects(BaseEffects);

    for(const TSubclassOf<UGameplayEffect>& EffectClass : BaseEffects)
    {
        AddBaseEffect(EffectClass);
    }
}

void UGRAbilitySystemComponent::AddKitStartupAbilities()
{
    TArray<FGameplayAbilityGrant> StartupAbilities;
    AbilityKit->GetStartupAbilities(StartupAbilities);

    for (const FGameplayAbilityGrant& Ability : StartupAbilities)
    {
        GrantAbility(Ability);
    }
    bStartupAbilitiesGiven = true;

    ForEachAbilityLambda([this](FGameplayAbilitySpec& AbilitySpec) {
        OnAbilitySpecChange.Broadcast(this, AbilitySpec);
    });
}

void UGRAbilitySystemComponent::ApplyKitStartupEffects()
{
    TArray<FGameplayEffectParameters> StartupEffects;
    AbilityKit->GetStartupEffects(StartupEffects);
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
