// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GRPlayerControllerComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/HUD.h"
#include "UI/HUD/GRHUDOverlayComponent.h"
#include "Input/GRInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"


UGRPlayerControllerComponent::UGRPlayerControllerComponent()
{
    SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UGRPlayerControllerComponent::AcknowledgePossession(APawn* aPawn)
{
    if (!IsValid(GetPlayerController()))
        return;

    AbilitySystemComponent = nullptr;
    FetchASC();

    AHUD* HUD = PlayerController->GetHUD();
    if (!IsValid(HUD))
        return;

    if (UGRHUDOverlayComponent* GRHUD = HUD->GetComponentByClass<UGRHUDOverlayComponent>())
    {
        GRHUD->InitOverlay(PlayerController, aPawn);
    }
}

void UGRPlayerControllerComponent::SetupInputComponent()
{
    if (!IsValid(GetPlayerController()))
        return;
    BindAbilityActions();
}


APlayerController* UGRPlayerControllerComponent::GetPlayerController()
{
    if (IsValid(PlayerController))
        return PlayerController;
    if (GetOwner())
        PlayerController = Cast<APlayerController>(GetOwner());
    return PlayerController;
}

void UGRPlayerControllerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(GetPlayerController()))
        FetchASC();
}

void UGRPlayerControllerComponent::FetchASC()
{
    APawn* Pawn = PlayerController->GetPawn();
    if (!IsValid(Pawn))
        return;

    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);
    if (IsValid(ASC))
        AbilitySystemComponent = Cast<UGRAbilitySystemComponent>(ASC);
}

void UGRPlayerControllerComponent::BindAbilityActions()
{
    if (!IsValid(AbilityInputConfig))
    {
        UE_LOG(LogTemp, Warning, TEXT("No GasRpg InputConfig set in player controller component. Abilities have no input mapping"));
        return;
    }

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
    if (!EnhancedInputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent is not a UEnhancedInputComponent. The GasRpg abilities won't get triggered"));
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

void UGRPlayerControllerComponent::AbilityInputTagPressed(FGameplayTag InputTag)
{
    if (IsValid(AbilitySystemComponent))
    {
        AbilitySystemComponent->AbilityInputTagPressed(InputTag);
    }
}

void UGRPlayerControllerComponent::AbilityInputTagReleased(FGameplayTag InputTag)
{
    if (IsValid(AbilitySystemComponent))
    {
        AbilitySystemComponent->AbilityInputTagReleased(InputTag);
    }
}

void UGRPlayerControllerComponent::AbilityInputTagHeld(FGameplayTag InputTag)
{
    if (IsValid(AbilitySystemComponent))
    {
        AbilitySystemComponent->AbilityInputTagHeld(InputTag);
    }
}
