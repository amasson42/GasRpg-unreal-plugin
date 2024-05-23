// Copyright Amasson


#include "UI/WidgetController/Components/GRAbilitiesInputWcc.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"


void UGRAbilitiesInputWcc::Initialize(UGRAbilitySystemComponent* ASC)
{
    AbilitySystemComponent = ASC;
}

void UGRAbilitiesInputWcc::BroadcastValues()
{
    if (IsValid(AbilitySystemComponent))
    {
        OnAbilitySpecChange(AbilitySystemComponent, FGameplayAbilitySpec());
    }
}

void UGRAbilitiesInputWcc::BindCallbacksToDependencies()
{
    if (IsValid(AbilitySystemComponent))
    {
        AbilitySystemComponent->OnAbilitySpecChange.AddUObject(this, &ThisClass::OnAbilitySpecChange);
        AbilitySystemComponent->OnAbilitySpecRemoving.AddUObject(this, &ThisClass::OnAbilitySpecRemoving);
    }
}

void UGRAbilitiesInputWcc::OnAbilitySpecChange(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec)
{
    TSet<FGameplayTag> NewAbilitiesInputTags;

    ASC->ForEachAbilityLambda([this, ASC, &NewAbilitiesInputTags](FGameplayAbilitySpec& AbilitySpec)
    {
        FGameplayTag AbilityTag = ASC->GetAbilityIDTagFromAbility(AbilitySpec.Ability);

        FGameplayTag InputTag = ASC->GetInputTagFromAbilitySpec(AbilitySpec);
        NewAbilitiesInputTags.Add(InputTag);
        if (InputTag.IsValid())
        {
            OnAbilityInputChange.Broadcast(InputTag, AbilityTag);
        }
    });

    for (const FGameplayTag& InputTag : AbilitiesInputTags)
    {
        if (!NewAbilitiesInputTags.Contains(InputTag))
        {
            OnAbilityInputRemoved.Broadcast(InputTag);
        }
    }
    AbilitiesInputTags = NewAbilitiesInputTags;
}

void UGRAbilitiesInputWcc::OnAbilitySpecRemoving(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec)
{
    FGameplayTag InputTag = ASC->GetInputTagFromAbilitySpec(AbilitySpec);
    if (InputTag.IsValid())
    {
        OnAbilityInputRemoved.Broadcast(InputTag);
    }
}
