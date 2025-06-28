// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/Components/GRVitalAttributesWcc.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRVitalAttributeSet.h"


void UGRVitalAttributesWcc::BroadcastValues()
{
    if (AttributeSet)
    {
        OnHealthChanged.Broadcast(AttributeSet->GetHealth());
        OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
    }
}

void UGRVitalAttributesWcc::BindCallbacksToDependencies()
{
    if (AttributeSet && AbilitySystemComponent)
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
            AttributeSet->GetHealthAttribute()
        ).AddLambda([this](const FOnAttributeChangeData& Data) {
            OnHealthChanged.Broadcast(Data.NewValue);
        });

        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
            AttributeSet->GetMaxHealthAttribute()
        ).AddLambda([this](const FOnAttributeChangeData& Data) {
            OnMaxHealthChanged.Broadcast(Data.NewValue);
        });
    }

}

void UGRVitalAttributesWcc::SetObservedActor(AActor* Actor)
{
    Super::SetObservedActor(Actor);

    AttributeSet = Cast<UGRVitalAttributeSet>(const_cast<UAttributeSet*>(AbilitySystemComponent->GetAttributeSet(UGRVitalAttributeSet::StaticClass())));
}
