// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GRPlayerController.h"
#include "UI/HUD/GRHUD.h"
#include "EnhancedInputComponent.h"
#include "Input/GRInputConfig.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


AGRPlayerController::AGRPlayerController()
{
    bReplicates = true;
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

void AGRPlayerController::AcknowledgePossession(APawn* aPawn)
{
    if (AGRHUD* HUD = GetHUD<AGRHUD>())
    {
        HUD->InitOverlay();
    }
}

void AGRPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    BindAbilityActions();
}

void AGRPlayerController::BindAbilityActions()
{
    if (!IsValid(AbilityInputConfig))
    {
        UE_LOG(LogTemp, Warning, TEXT("No GasRpg InputConfig set in player controller. Abilities have no input mapping"));
        return;
    }

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent is not a subclass of UGRInputComponent. The GasRpg abilities won't get triggered"));
        return;
    }

    for (const FAbilityInputTagAction& InputTagAction : AbilityInputConfig->AbilityInputTagActions)
    {
        const FGameplayTag& InputTag = InputTagAction.Tag;
        const UInputAction* InputAction = InputTagAction.Action;

        if (!(IsValid(InputAction) && InputTag.IsValid()))
            continue;

        EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::AbilityInputTagPressed, InputTag);
        EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::AbilityInputTagReleased, InputTag);
        EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::AbilityInputTagHeld, InputTag);
    }
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
