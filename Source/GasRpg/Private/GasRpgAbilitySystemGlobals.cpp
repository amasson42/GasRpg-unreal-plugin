// Fill out your copyright notice in the Description page of Project Settings.


#include "GasRpgAbilitySystemGlobals.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"

FGameplayEffectContext* UGasRpgAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FGRGameplayEffectContext();
}
