// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRCharacterBase.h"
#include "Player/GRPlayerController.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/Effect/GRPrimaryAttributesBaseEffect.h"
#include "AbilitySystem/Effect/GRSecondaryAttributesBaseEffect.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "AbilitySystem/GRVitalAttributeSet.h"
#include "Data/GRAbilityKit.h"
#include "FactionSystem/FactionData.h"
#include "Component/GasRpgCharacterBaseComponent.h"


AGRCharacterBase::AGRCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AGRCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AGRCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}


/** RpgCharacter Interface */

int32 AGRCharacterBase::GetCharacterLevel_Implementation() const
{
    return 1;
}

FVector AGRCharacterBase::GetSocketLocation_Implementation(FGameplayTag SocketTagName) const
{
    return GetActorLocation();
}

USceneComponent* AGRCharacterBase::GetSocketComponent_Implementation(FGameplayTag SocketTag) const
{
    return GetRootComponent();
}

FRpgCharacterMontage AGRCharacterBase::GetMontage_Implementation(FGameplayTag MontageTag) const
{
    const FRpgCharacterMontageArray *MontageArray = RpgMontages.Find(MontageTag);
    if (!MontageArray || MontageArray->Montages.IsEmpty())
        return FRpgCharacterMontage();

    return MontageArray->Montages[FMath::RandRange(0, MontageArray->Montages.Num() - 1)];
}

void AGRCharacterBase::ActivateRpgEventForTag_Implementation(FGameplayTag RpgEventTag, UObject* Activator)
{
    FObjectSet* Set = RpgEventActivators.Find(RpgEventTag);
    if (Set)
    {
        Set->Objects.Add(Activator);
    }
    else
    {
        FObjectSet NewSet;
        NewSet.Objects.Add(Activator);
        RpgEventActivators.Add(RpgEventTag, NewSet);
        ToggleRpgEventForTag(RpgEventTag, true);
    }
}

void AGRCharacterBase::DeactivateRpgEventForTag_Implementation(FGameplayTag RpgEventTag, UObject* Activator)
{
    FObjectSet* Set = RpgEventActivators.Find(RpgEventTag);
    if (Set)
    {
        Set->Objects.Remove(Activator);
        if (Set->Objects.IsEmpty())
        {
            RpgEventActivators.Remove(RpgEventTag);
            ToggleRpgEventForTag(RpgEventTag, false);
        }
    }
}


bool AGRCharacterBase::IsDead_Implementation() const
{
    if (!IsValid(AttributeSet))
		return false;

	if (UGRVitalAttributeSet* AS = Cast<UGRVitalAttributeSet>(AttributeSet))
	{
		return AS->GetHealth() <= 0.0f;
	}

	return false;
}

IRpgCharacterInterface::FOnASCRegisteredDelegate& AGRCharacterBase::GetOnASCRegisteredDelegate()
{
    return OnASCRegistered;
}

FOnDeathBroadcastSignature& AGRCharacterBase::GetOnDeathDelegate()
{
    return OnDeath;
}

/** Ability System */

void AGRCharacterBase::InitAbilitySystem()
{
	if (UGRAbilitySystemComponent* ASC = Cast<UGRAbilitySystemComponent>(AbilitySystemComponent))
    {
        ASC->AbilitySystemInitDone();
    }
	AbilitySystemInitialized(AbilitySystemComponent);
	OnASCRegistered.Broadcast(AbilitySystemComponent);
}

void AGRCharacterBase::AbilitySystemInitialized_Implementation(UAbilitySystemComponent* ASC)
{
	
}
