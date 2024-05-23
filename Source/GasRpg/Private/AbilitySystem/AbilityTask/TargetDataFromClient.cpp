// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetDataFromClient.h"
#include "AbilitySystemComponent.h"


void UAbilityTask_TargetDataFromClient::Activate()
{
    const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
    if (bIsLocallyControlled)
    {
        SendTargetData();
    }
    else
    {
        WaitToReceiveTargetData();
    }
}

void UAbilityTask_TargetDataFromClient::SendTargetData()
{
    FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

    FGameplayAbilityTargetDataHandle DataHandle;
    if (!AddTargetDataToHandle(DataHandle))
    {
        if (ShouldBroadcastAbilityTaskDelegates())
            NoData.Broadcast();
        return;
    }

    AbilitySystemComponent->ServerSetReplicatedTargetData(
        GetAbilitySpecHandle(),
        GetActivationPredictionKey(),
        DataHandle,
        FGameplayTag(),
        AbilitySystemComponent->ScopedPredictionKey
    );

    if (ShouldBroadcastAbilityTaskDelegates())
        ValidData.Broadcast(DataHandle);

}

void UAbilityTask_TargetDataFromClient::WaitToReceiveTargetData()
{
    const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
    const FPredictionKey ActivationKey = GetActivationPredictionKey();
    UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

    ASC->AbilityTargetDataSetDelegate(SpecHandle, ActivationKey)
        .AddUObject(this, &ThisClass::OnTargetDataReplicatedCallback);
    const bool bCalledDelegate = ASC->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationKey);
    if (!bCalledDelegate)
    {
        SetWaitingOnRemotePlayerData();
    }
}

void UAbilityTask_TargetDataFromClient::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
    AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ValidData.Broadcast(DataHandle);
    }
}
