// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRMainAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/GRMainAttributeList.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "Character/RpgCharacterInterface.h"
#include "GasRpgGameplayTags.h"
#include "Player/GRPlayerController.h"


UGRMainAttributeSet::UGRMainAttributeSet()
{
	
}

void UGRMainAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

#define DeclareAttributeReplication(AttributeName, CategoryName) \
	DOREPLIFETIME_CONDITION_NOTIFY(UGRMainAttributeSet, AttributeName, COND_None, REPNOTIFY_Always);

	FOREACH_ATTRIBUTE_Replicated(DeclareAttributeReplication);
}

#define ImplementAttribute_OnRep(AttributeName, CategoryName) \
void UGRMainAttributeSet::OnRep_##AttributeName(const FGameplayAttributeData& Old##AttributeName) const \
{ \
   	GAMEPLAYATTRIBUTE_REPNOTIFY(UGRMainAttributeSet, AttributeName, Old##AttributeName); \
}

FOREACH_ATTRIBUTE_Replicated(ImplementAttribute_OnRep)

void UGRMainAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);


}

void UGRMainAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    #define CheckMaxVitalAttributeChange(AttributeName, Category) \
        if (Attribute == GetMax##AttributeName##Attribute()) \
        { \
            float Percent = Get##AttributeName() / OldValue; \
            Set##AttributeName(Percent * NewValue); \
        }

    FOREACH_ATTRIBUTE_Vital_NoMax(CheckMaxVitalAttributeChange)
}

void UGRMainAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    #define ClampVitalToMax(AttributeName, Category) \
        if (Data.EvaluatedData.Attribute == Get##AttributeName##Attribute()) \
            Set##AttributeName(FMath::Clamp(Get##AttributeName(), 0.0f, GetMax##AttributeName()));

    FOREACH_ATTRIBUTE_Vital_NoMax(ClampVitalToMax)

    if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleModificationData_IncomingDamage(Data);
	}
}

void UGRMainAttributeSet::ExtractEffectModProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
    UGRAbilitySystemLibrary::ExtractPropertiesFromGameplayEffectContextHandle(Data.EffectSpec.GetContext(), Props);

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UGRMainAttributeSet::HandleModificationData_IncomingDamage(const FGameplayEffectModCallbackData& Data)
{
	FEffectProperties Props;
	ExtractEffectModProperties(Data, Props);

	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.0f);

	if (LocalIncomingDamage != 0.0f)
	{
		const bool bWasAlive = GetHealth() > 0.0f;
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0, GetMaxHealth()));

		bool bFatal = NewHealth <= 0.0f;

        PopFloatingDamages(LocalIncomingDamage, Data, Props);

        SendGameplayEventToSourceActor(FGRGameplayTags::Get().Event_AbilitySystem_DamageApplied, LocalIncomingDamage, Data, Props);

		if (bWasAlive && bFatal)
		{
			if (IRpgCharacterInterface* CombatInterface = Cast<IRpgCharacterInterface>(Props.TargetAvatarActor))
			{
				IRpgCharacterInterface::Execute_Die(Props.TargetAvatarActor, Data.EffectSpec);
				CombatInterface->GetOnDeathDelegate().Broadcast(Props.TargetAvatarActor, Data.EffectSpec);
			}

            SendGameplayEventToSourceActor(FGRGameplayTags::Get().Event_AbilitySystem_UnitKilled, 0, Data, Props);
		}

	}

}

void UGRMainAttributeSet::PopFloatingDamages(float Damages, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props)
{
    AGRPlayerController* SourcePC = IsValid(Props.SourceController) ? Cast<AGRPlayerController>(Props.SourceController) : nullptr;
    AGRPlayerController* TargetPC = IsValid(Props.TargetController) ? Cast<AGRPlayerController>(Props.TargetController) : nullptr;
    if (SourcePC || TargetPC)
    {
        FFloatingDamage FloatingDamage;

        FGameplayTagContainer AllAssetTags;
        Data.EffectSpec.GetAllAssetTags(AllAssetTags);
        UGRAbilitySystemLibrary::GetMatchingTagsFromTagContainer(
            AllAssetTags,
            FGRGameplayTags::Get().DamageTag,
            FloatingDamage.Tags
        );
        FloatingDamage.Source = Props.SourceAvatarActor;
        FloatingDamage.Target = Props.TargetAvatarActor;
        FloatingDamage.Damages = Damages;

        if (UGRAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle))
            FloatingDamage.Tags.AddTag(FGRGameplayTags::Get().DamageTag_Blocked);
        if (UGRAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle))
            FloatingDamage.Tags.AddTag(FGRGameplayTags::Get().DamageTag_Critical);

        if (SourcePC)
            SourcePC->Client_ShowFloatingDamages(FloatingDamage);
        if (TargetPC)
            TargetPC->Client_ShowFloatingDamages(FloatingDamage);
    }
}

void UGRMainAttributeSet::SendGameplayEventToSourceActor(const FGameplayTag& EventTag, float Magnitude, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props)
{
    FGameplayEventData Payload;
    Payload.EventTag = EventTag;
    Payload.Instigator = Props.SourceAvatarActor;
    Payload.Target = Props.TargetAvatarActor;
    Payload.OptionalObject = Data.EffectSpec.GetContext().GetAbility();
    Payload.ContextHandle = Props.EffectContextHandle;
    Payload.EventMagnitude = Magnitude;
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        Props.SourceAvatarActor,
        EventTag,
        Payload
    );
}
