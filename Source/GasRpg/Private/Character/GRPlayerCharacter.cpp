// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/GRPlayerState.h"
#include "AbilitySystem/GRVitalAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"


AGRPlayerCharacter::AGRPlayerCharacter()
{

}

void AGRPlayerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    InitAbilitySystem();
}

void AGRPlayerCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    InitAbilitySystem();
}

void AGRPlayerCharacter::InitAbilitySystem()
{
    APlayerState* PS = GetPlayerState();
    if (!IsValid(PS))
    {
        UE_LOG(LogTemp, Warning, TEXT("GRPlayerCharacter with no valid player state. %s"), *UKismetSystemLibrary::GetDisplayName(this));
        return;
    }

    IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(PS);
    if (AbilitySystemInterface == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("GRPlayerCharacter with no valid ability system interface. %s"), *UKismetSystemLibrary::GetDisplayName(this));
        return;
    }

    AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
    AbilitySystemComponent->InitAbilityActorInfo(PS, this);
    AttributeSet = const_cast<UGRVitalAttributeSet*>(AbilitySystemComponent->GetSet<UGRVitalAttributeSet>());

    Super::InitAbilitySystem();
}
