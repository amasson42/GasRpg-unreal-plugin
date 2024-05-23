// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GRPlayerController.h"
#include "UI/HUD/GRHUD.h"
#include "Input/GRInputComponent.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


AGRPlayerController::AGRPlayerController()
{
    bReplicates = true;
}

void AGRPlayerController::PawnRestart(APawn* aPawn)
{
    BP_PawnRestart(aPawn);

    if (AGRHUD* HUD = GetHUD<AGRHUD>())
    {
        HUD->InitOverlay();
    }
}

void AGRPlayerController::Client_ShowFloatingDamages_Implementation(const FFloatingDamage& FloatingDamage)
{
    ShowFloatingDamages(FloatingDamage);
}

void AGRPlayerController::ShowFloatingDamages_Implementation(const FFloatingDamage& FloatingDamage)
{

}

void AGRPlayerController::BeginPlay()
{
    Super::BeginPlay();

}

void AGRPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!IsValid(AbilityInputConfig))
    {
        UE_LOG(LogTemp, Warning, TEXT("No GasRpg InputConfig set in player controller. Abilities have no input mapping"));
        return;
    }

    UGRInputComponent* GasRpgInputComponent = Cast<UGRInputComponent>(InputComponent);
    if (!GasRpgInputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent is not a subclass of UGRInputComponent. The GasRpg abilities won't get triggered"));
        return;
    }
    
    GasRpgInputComponent->BindAbilityActions(AbilityInputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AGRPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
    if (UGRAbilitySystemComponent* ASC = GetASC())
    {
        ASC->AbilityInputTagPressed(InputTag);
    }
}

void AGRPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
    if (UGRAbilitySystemComponent* ASC = GetASC())
    {
        ASC->AbilityInputTagReleased(InputTag);
    }
}

void AGRPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
    if (UGRAbilitySystemComponent* ASC = GetASC())
    {
        ASC->AbilityInputTagHeld(InputTag);
    }
}

UGRAbilitySystemComponent* AGRPlayerController::GetASC()
{
    if (!AbilitySystemComponent)
    {
        UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
        if (IsValid(ASC))
            AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(ASC);
    }
    return AbilitySystemComponent;
}
