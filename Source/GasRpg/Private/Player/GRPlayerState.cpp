// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GRPlayerState.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRMainAttributeSet.h"


AGRPlayerState::AGRPlayerState()
{
    NetUpdateFrequency = 100.0f;

    AbilitySystemComponent = CreateDefaultSubobject<UGRAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UGRMainAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGRPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}
