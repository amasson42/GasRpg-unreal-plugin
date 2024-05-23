// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GRHUD.h"
#include "UI/WidgetController/GROverlayController.h"
#include "Player/GRPlayerState.h"
#include "UI/WidgetController.h"
#include "UI/ControllableUserWidget.h"


UGROverlayController* AGRHUD::GetOverlayController()
{
    if (!OverlayController)
    {
        UWidgetController* NewWidgetController = UWidgetController::MakeWidgetController(
            this,
            OverlayControllerClass,
            GetActorToObserve()
        );

        OverlayController = Cast<UGROverlayController>(NewWidgetController);
    }
    return OverlayController;
}

void AGRHUD::InitOverlay()
{
    checkf(OverlayWidgetClass, TEXT("HUD: Invalid class for OverlayWidgetClass"));
    checkf(OverlayControllerClass, TEXT("HUD: Invalid class for OverlayControllerClass"));

    ClearOverlay();

    UGROverlayController* WidgetController = GetOverlayController();

    OverlayWidget = CreateWidget<UControllableUserWidget>(GetWorld(), OverlayWidgetClass);

    OverlayWidget->SetWidgetController(WidgetController);
    WidgetController->BroadcastValues();

    OverlayWidget->AddToViewport();
}

void AGRHUD::ClearOverlay()
{
    if (IsValid(OverlayWidget))
        OverlayWidget->RemoveFromParent();

    OverlayController = nullptr;
    OverlayWidget = nullptr;
}

AActor* AGRHUD::GetActorToObserve() const
{
    AActor* ObservedActor = nullptr;

    APlayerController* PC = GetOwningPlayerController();
    if (IsValid(PC))
    {
        // Type is actor to make ternary operator understand
        AActor* PS = PC->GetPlayerState<AGRPlayerState>();
        ObservedActor = IsValid(PS) ? PS : PC;
    }

    return ObservedActor;
}
