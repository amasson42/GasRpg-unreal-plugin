// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/GRWidgetControllerBase.h"
#include "Character/GRCharacterBase.h"
#include "Player/GRPlayerState.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRVitalAttributeSet.h"


void UGRWidgetControllerBase::ObservedActorSet()
{
    Super::ObservedActorSet();

    if (IsValid(Pawn))
        GRCharacter = Cast<AGRCharacterBase>(Pawn);

    if (IsValid(PlayerState))
        GRPlayerState = Cast<AGRPlayerState>(PlayerState);

    if (IsValid(GRCharacter))
    {
        if (UAbilitySystemComponent* ASC = GRCharacter->GetAbilitySystemComponent())
            AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(ASC);
        if (UAttributeSet* AS = GRCharacter->GetAttributeSet())
            AttributeSet = Cast<UGRVitalAttributeSet>(AS);
    }
    else if (IsValid(GRPlayerState))
    {
        if (UAbilitySystemComponent* ASC = GRPlayerState->GetAbilitySystemComponent())
            AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(ASC);
        AttributeSet = GRPlayerState->GetAttributeSet();
    }
    else if (IsValid(Actor))
    {
        AbilitySystemComponent = Actor->GetComponentByClass<UGRAbilitySystemComponent>();
        AttributeSet = nullptr;
    }
}
