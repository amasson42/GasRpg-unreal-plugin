// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/GRPlayerState.h"
#include "AbilitySystem/GRMainAttributeSet.h"
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
    AGRPlayerState* PS = GetPlayerState<AGRPlayerState>();

    if (!IsValid(PS))
    {
        UE_LOG(LogTemp, Warning, TEXT("GRPlayerCharacter with no valid player state. %s"), *UKismetSystemLibrary::GetDisplayName(this));
        return;
    }
    check(PS);

    AbilitySystemComponent = PS->GetAbilitySystemComponent();
    AbilitySystemComponent->InitAbilityActorInfo(PS, this);
    AttributeSet = PS->GetAttributeSet();

    Super::InitAbilitySystem();
}

// int32 AGRPlayerCharacter::GetPlayerLevel_Implementation() const
// {
//     if (AGRPlayerState* PS = GetPlayerState<AGRPlayerState>())
//     {
//         return PS->GetPlayerLevel();
//     }
//     return 0;
// }

// ULevelingExperienceComponent* AGRPlayerCharacter::GetLevelingExperienceComponent_Implementation() const
// {
//     if (AGRPlayerState* PS = GetPlayerState<AGRPlayerState>())
//     {
//         return PS->GetLevelingExperience();
//     }
//     return nullptr;
// }