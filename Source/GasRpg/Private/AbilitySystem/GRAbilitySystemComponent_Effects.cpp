// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRAbilitySystemComponent.h"


FActiveGameplayEffectHandle UGRAbilitySystemComponent::ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey)
{
    // for (int32 Index = EffectInterceptors.Num() - 1; Index >= 0; --Index)
    // {
    //     if (!IsValid(EffectInterceptors[Index]) || !EffectInterceptors[Index]->Implements<UGameplayEffectInterceptor>())
    //         EffectInterceptors.RemoveAt(Index);
    // }

    // for (UObject* Interceptor : EffectInterceptors)
    // {
    //     bool bIntercepted = false;

    //     IGameplayEffectInterceptor::Execute_WillApplyGameplayEffectSpec(Interceptor, GameplayEffect, bIntercepted);

    //     if (bIntercepted)
    //         return FActiveGameplayEffectHandle();
    // }

    return Super::ApplyGameplayEffectSpecToSelf(GameplayEffect, PredictionKey);
}

// void UGRAbilitySystemComponent::AddGameplayEffectInterceptor(UObject* Interceptor)
// {
//     if (!IsValid(Interceptor) || !Interceptor->Implements<UGameplayEffectInterceptor>())
//         return;

//     EffectInterceptors.Add(Interceptor);
// }

// void UGRAbilitySystemComponent::RemoveGameplayEffectInterceptor(UObject* Interceptor)
// {
//     EffectInterceptors.Remove(Interceptor);
// }

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
