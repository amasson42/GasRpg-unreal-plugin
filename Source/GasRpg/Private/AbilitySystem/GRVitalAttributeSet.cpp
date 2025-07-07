// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRVitalAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "GasRpgGameplayTags.h"
#include "Player/GRPlayerControllerFloatingDamagesComponent.h"


UGRVitalAttributeSet::UGRVitalAttributeSet()
{
	
}

void UGRVitalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGRVitalAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGRVitalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UGRVitalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGRVitalAttributeSet, Health, OldHealth);
}
void UGRVitalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGRVitalAttributeSet, MaxHealth, OldMaxHealth);
}

void UGRVitalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);


}

void UGRVitalAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		float Percent = GetHealth() / OldValue;
		SetHealth(Percent * NewValue);
	}
}

void UGRVitalAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
    else if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
		HandleModificationData_IncomingDamage(Data);
}

void UGRVitalAttributeSet::ExtractEffectModProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
    UGRAbilitySystemLibrary::ExtractPropertiesFromGameplayEffectContextHandle(Data.EffectSpec.GetContext(), Props);

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UGRVitalAttributeSet::HandleModificationData_IncomingDamage(const FGameplayEffectModCallbackData& Data)
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
			OnDeath.Broadcast(this, Data.EffectSpec);

            SendGameplayEventToSourceActor(FGRGameplayTags::Get().Event_AbilitySystem_UnitKilled, 0, Data, Props);
		}
	}

}

void UGRVitalAttributeSet::PopFloatingDamages(float Damages, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props)
{
    APlayerController* SourcePlayerController = IsValid(Props.SourceController) ? Cast<APlayerController>(Props.SourceController) : nullptr;
	UGRPlayerControllerFloatingDamagesComponent* SourceComponent =
		IsValid(SourcePlayerController) ?
		SourcePlayerController->GetComponentByClass<UGRPlayerControllerFloatingDamagesComponent>() :
		nullptr;
    APlayerController* TargetPlayerController = IsValid(Props.TargetController) ? Cast<APlayerController>(Props.TargetController) : nullptr;
	UGRPlayerControllerFloatingDamagesComponent* TargetComponent =
		IsValid(TargetPlayerController) ?
		TargetPlayerController->GetComponentByClass<UGRPlayerControllerFloatingDamagesComponent>() :
		nullptr;

	if (IsValid(SourceComponent) || IsValid(TargetComponent))
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
    
        if (SourceComponent)
            SourceComponent->Client_ShowFloatingDamages(FloatingDamage);
        if (TargetComponent)
            TargetComponent->Client_ShowFloatingDamages(FloatingDamage);
    }
}

void UGRVitalAttributeSet::SendGameplayEventToSourceActor(const FGameplayTag& EventTag, float Magnitude, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props)
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
