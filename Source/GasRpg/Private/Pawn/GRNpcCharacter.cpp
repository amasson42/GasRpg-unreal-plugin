// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/GRNpcCharacter.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRVitalAttributeSet.h"
#include "AbilitySystem/GRMovementAttributeSet.h"


AGRNpcCharacter::AGRNpcCharacter()
{
    AbilitySystemComponent = CreateDefaultSubobject<UGRAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    CreateDefaultSubobject<UGRVitalAttributeSet>("VitalAttributeSet");
    CreateDefaultSubobject<UGRMovementAttributeSet>("MovementAttributeSet");
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
