// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"


void UGRAbilitySystemComponent::AddBaseEffect(const TSubclassOf<UGameplayEffect>& EffectClass)
{
    if (IsValid(EffectClass))
    {
        FGameplayEffectContextHandle EffectContext = MakeEffectContext();
        EffectContext.AddSourceObject(GetAvatarActor());
        auto OutgoingSpec = MakeOutgoingSpec(EffectClass, BaseEffectsLevel, EffectContext);
        FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectSpecToSelf(*OutgoingSpec.Data.Get());

        BaseEffectsHandles.Add(EffectHandle);
    }
}

void UGRAbilitySystemComponent::SetBaseEffectsLevel(float Level)
{
    BaseEffectsLevel = Level;
    for (const FActiveGameplayEffectHandle& Handle : BaseEffectsHandles)
    {
        SetActiveGameplayEffectLevel(Handle, Level);
    }
}
