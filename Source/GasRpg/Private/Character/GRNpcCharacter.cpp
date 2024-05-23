// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRNpcCharacter.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRMainAttributeSet.h"


AGRNpcCharacter::AGRNpcCharacter()
{
    AbilitySystemComponent = CreateDefaultSubobject<UGRAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UGRMainAttributeSet>("AttributeSet");
}

void AGRNpcCharacter::BeginPlay()
{
    Super::BeginPlay();

    InitAbilitySystem();
}

void AGRNpcCharacter::InitAbilitySystem()
{
    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    Super::InitAbilitySystem();
}
