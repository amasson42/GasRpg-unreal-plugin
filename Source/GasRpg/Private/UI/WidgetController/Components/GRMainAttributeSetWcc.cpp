// Amasson


#include "UI/WidgetController/Components/GRMainAttributeSetWcc.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRMainAttributeSet.h"
#include "AbilitySystem/GRMainAttributeList.h"
#include "GasRpgGameplayTags.h"


void UGRMainAttributeSetWcc::Initialize(UGRAbilitySystemComponent* ASC, UGRMainAttributeSet* AS)
{
    AbilitySystemComponent = ASC;
    AttributeSet = AS;
}

void UGRMainAttributeSetWcc::BroadcastValues()
{
    if (AttributeSet)
    {
        FGameplayTag Tag;
        float Value;

        #define INITIAL_VALUE_BROADCAST(AttributeName, CategoryName) \
            Tag = FGRGameplayTags::Get().Attributes_##CategoryName##_##AttributeName; \
            Value = AttributeSet->Get##AttributeName(); \
            OnAttributeChange.Broadcast(Tag, Value);

        FOREACH_ATTRIBUTE_Stats(INITIAL_VALUE_BROADCAST)

    }
}

void UGRMainAttributeSetWcc::BindCallbacksToDependencies()
{
    if (AbilitySystemComponent && AttributeSet)
    {

        #define BIND_CALLBACK_ATTRIBUTE(AttributeName, CategoryName) \
            AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->Get##AttributeName##Attribute()) \
                .AddLambda([this](const FOnAttributeChangeData& Data) { \
                    const FGameplayTag Tag = FGRGameplayTags::Get().Attributes_##CategoryName##_##AttributeName; \
                    const float Value = Data.NewValue; \
                    OnAttributeChange.Broadcast(Tag, Value); \
                });

        FOREACH_ATTRIBUTE_Stats(BIND_CALLBACK_ATTRIBUTE);

    }

}
