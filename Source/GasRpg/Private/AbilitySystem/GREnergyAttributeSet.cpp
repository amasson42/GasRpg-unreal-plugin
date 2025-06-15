// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GREnergyAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "GasRpgGameplayTags.h"


UGREnergyAttributeSet::UGREnergyAttributeSet()
{
	
}

void UGREnergyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGREnergyAttributeSet, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGREnergyAttributeSet, MaxEnergy, COND_None, REPNOTIFY_Always);
}

void UGREnergyAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGREnergyAttributeSet, Energy, OldEnergy);
}
void UGREnergyAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGREnergyAttributeSet, MaxEnergy, OldMaxEnergy);
}

void UGREnergyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);


}

void UGREnergyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxEnergyAttribute())
	{
		float Percent = GetEnergy() / OldValue;
		SetEnergy(Percent * NewValue);
	}
}

void UGREnergyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
		SetEnergy(FMath::Clamp(GetEnergy(), 0.0f, GetMaxEnergy()));
}
