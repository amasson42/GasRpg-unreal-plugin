// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/GRPlayerStateCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"


AGRPlayerStateCharacter::AGRPlayerStateCharacter()
{

}

void AGRPlayerStateCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    InitAbilitySystem();
}

void AGRPlayerStateCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    InitAbilitySystem();
}

void AGRPlayerStateCharacter::InitAbilitySystem(UGRAbilityKit* AbilityKit)
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

    Super::InitAbilitySystem(AbilityKit);
}
