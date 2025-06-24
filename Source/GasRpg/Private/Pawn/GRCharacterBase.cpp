// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/GRCharacterBase.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"


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

/** Ability System */

void AGRCharacterBase::WithInitializedAbilitySystem(const FWithInitializedAbilitySystemDelegate& Delegate)
{
    if (bASCInitialized)
        Delegate.ExecuteIfBound(AbilitySystemComponent);
    else
        OnAbilitySystemInitialized.Add(Delegate);
}

void AGRCharacterBase::InitAbilitySystem(UGRAbilityKit* AdditionalKit)
{
	if (UGRAbilitySystemComponent* ASC = Cast<UGRAbilitySystemComponent>(AbilitySystemComponent))
    {
        ASC->AbilitySystemInit(AdditionalKit);
    }
    bASCInitialized = true;
    OnAbilitySystemInitialized.Broadcast(AbilitySystemComponent);
}
