// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GRMovementAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"


UGRMovementAttributeSet::UGRMovementAttributeSet()
{
	
}

void UGRMovementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGRMovementAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGRMovementAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGRMovementAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
}

void UGRMovementAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGRMovementAttributeSet, Stamina, OldStamina);
}

void UGRMovementAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGRMovementAttributeSet, MaxStamina, OldMaxStamina);
}

void UGRMovementAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGRMovementAttributeSet, MovementSpeed, OldMovementSpeed);
}


void UGRMovementAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);


}

void UGRMovementAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxStaminaAttribute())
	{
		float Percent = GetStamina() / OldValue;
		SetStamina(Percent * NewValue);
	}
}

void UGRMovementAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	else if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
		SetMovementSpeed(FMath::Max(0.0f, GetMovementSpeed()));
}
