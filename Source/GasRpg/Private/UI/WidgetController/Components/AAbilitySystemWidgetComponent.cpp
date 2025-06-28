// Copyright Amasson


#include "UI/WidgetController/Components/AAbilitySystemWidgetComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"


void UAAbilitySystemWidgetComponent::SetObservedActor(AActor* Actor)
{
    if (IAbilitySystemInterface* IASC = Cast<IAbilitySystemInterface>(Actor))
    {
        AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(IASC->GetAbilitySystemComponent());
    }
}
