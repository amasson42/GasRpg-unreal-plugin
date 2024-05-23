// Copyright Amasson


#include "UI/WidgetController/Components/GRAbilitiesStatusWcc.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"


void UGRAbilitiesStatusWcc::Initialize(UGRAbilitySystemComponent* ASC)
{
    AbilitySystemComponent = ASC;
}

void UGRAbilitiesStatusWcc::BroadcastValues()
{
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->ForEachAbilityLambda([this](FGameplayAbilitySpec& AbilitySpec)
        {
            OnAbilitySpecChange(AbilitySystemComponent, AbilitySpec);
        });
    }
}

void UGRAbilitiesStatusWcc::BindCallbacksToDependencies()
{
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->OnAbilitySpecChange.AddUObject(this, &ThisClass::OnAbilitySpecChange);
        AbilitySystemComponent->OnAbilitySpecRemoving.AddUObject(this, &ThisClass::OnAbilitySpecRemoving);
    }
}

// void UGRAbilitiesStatusWcc::GetAbilityBookCategories(TSet<FName>& Names) const
// {
//     if (AbilitiesBook)
//     {
//         for (const TPair<FGameplayTag, FAuraAbilityInfo>& BookLine : AbilitiesBook->GetAbilities())
//         {
//             Names.Add(BookLine.Value.TreeName);
//         }
//     }
// }

// void UGRAbilitiesStatusWcc::GetAllAbilitiesInformations(TArray<FAuraAbilityInfo>& AbilityBook) const
// {
//     if (AbilitiesBook)
//     {
//         for (const TPair<FGameplayTag, FAuraAbilityInfo>& BookLine : AbilitiesBook->GetAbilities())
//         {
//             FAuraAbilityInfo AbilityInfo = BookLine.Value;
//             AbilityBook.Add(AbilityInfo);
//         }
//     }
// }

void UGRAbilitiesStatusWcc::OnAbilitySpecChange(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec)
{
    const FGameplayTag AbilityID = ASC->GetAbilityIDTagFromAbility(AbilitySpec.Ability);
    if (AbilityID.IsValid())
    {
        const FGameplayTag StatusTag = ASC->GetStatusTagFromAbilitySpec(AbilitySpec);
        int32 Level = AbilitySpec.Level;
        OnAbilityStatusUpdated.Broadcast(AbilityID, StatusTag, Level);
    }
}

void UGRAbilitiesStatusWcc::OnAbilitySpecRemoving(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec)
{
    const FGameplayTag AbilityID = ASC->GetAbilityIDTagFromAbility(AbilitySpec.Ability);
    if (AbilityID.IsValid())
    {
        OnAbilityStatusRemoved.Broadcast(AbilityID);
    }
}
