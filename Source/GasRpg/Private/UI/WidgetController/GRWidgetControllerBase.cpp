// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/GRWidgetControllerBase.h"
#include "Pawn/GRCharacterBase.h"
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
        {
            AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(ASC);
            if (const UAttributeSet* AS = ASC->GetAttributeSet(UGRVitalAttributeSet::StaticClass()))
                AttributeSet = Cast<UGRVitalAttributeSet>(const_cast<UAttributeSet*>(AS));
        }
    }
    else if (IsValid(GRPlayerState))
    {
        if (UAbilitySystemComponent* ASC = GRPlayerState->GetAbilitySystemComponent())
        {
            AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(ASC);
            if (const UAttributeSet* AS = ASC->GetAttributeSet(UGRVitalAttributeSet::StaticClass()))
                AttributeSet = Cast<UGRVitalAttributeSet>(const_cast<UAttributeSet*>(AS));
        }
    }
    else if (IsValid(Actor))
    {
        AbilitySystemComponent = Actor->GetComponentByClass<UGRAbilitySystemComponent>();
        AttributeSet = nullptr;
    }
}
