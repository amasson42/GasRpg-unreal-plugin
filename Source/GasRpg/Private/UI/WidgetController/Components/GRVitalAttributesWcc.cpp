// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/Components/GRVitalAttributesWcc.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRMainAttributeSet.h"


void UGRVitalAttributesWcc::Initialize(UGRAbilitySystemComponent* ASC, UGRMainAttributeSet* AS)
{
    AbilitySystemComponent = ASC;
    AttributeSet = AS;
}

void UGRVitalAttributesWcc::BroadcastValues()
{
    if (AttributeSet)
    {
        #define BroadcastAttributeValue(AttributeName, CategoryName) \
            On##AttributeName##Changed.Broadcast(AttributeSet->Get##AttributeName());

        FOREACH_ATTRIBUTE_Vital(BroadcastAttributeValue)
    }
}

void UGRVitalAttributesWcc::BindCallbacksToDependencies()
{
    if (AttributeSet && AbilitySystemComponent)
    {
        #define BindOnAttributeChange(AttributeName, CategoryName) \
            AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate( \
                AttributeSet->Get##AttributeName##Attribute() \
            ).AddLambda([this](const FOnAttributeChangeData& Data) { \
                On##AttributeName##Changed.Broadcast(Data.NewValue); \
            }); \

        FOREACH_ATTRIBUTE_Vital(BindOnAttributeChange)
    }

}


#define DeclareIsVitalRelevant(AttributeName, CategoryName) \
bool UGRVitalAttributesWcc::Is##AttributeName##Relevant() const \
{ \
    if (!IsValid(AttributeSet)) \
        return false; \
    \
    return AttributeSet->GetMax##AttributeName() > 0.0f; \
}

FOREACH_ATTRIBUTE_Vital_NoMax(DeclareIsVitalRelevant)
