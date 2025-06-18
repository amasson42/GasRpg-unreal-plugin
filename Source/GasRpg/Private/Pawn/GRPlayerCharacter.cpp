// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/GRPlayerCharacter.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRVitalAttributeSet.h"
#include "AbilitySystem/GRMovementAttributeSet.h"


AGRPlayerCharacter::AGRPlayerCharacter()
{
    AbilitySystemComponent = CreateDefaultSubobject<UGRAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    CreateDefaultSubobject<UGRVitalAttributeSet>("VitalAttributeSet");
    CreateDefaultSubobject<UGRMovementAttributeSet>("MovementAttributeSet");
}

void AGRPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    InitAbilitySystem();
}

void AGRPlayerCharacter::InitAbilitySystem()
{
    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    Super::InitAbilitySystem();
}
