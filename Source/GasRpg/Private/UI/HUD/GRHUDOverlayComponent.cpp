// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GRHUDOverlayComponent.h"
#include "UI/WidgetController.h"
#include "UI/ControllableUserWidget.h"
#include "GameFramework/PlayerController.h"


void UGRHUDOverlayComponent::InitOverlay(APlayerController* OwningPlayerController, AActor* ObservedActor)
{
	checkf(OverlayWidgetClass, TEXT("HUD: Invalid class for OverlayWidgetClass"));
	checkf(OverlayControllerClass, TEXT("HUD: Invalid class for OverlayControllerClass"));

	TSubclassOf<UControllableUserWidget> WidgetClass = OverlayWidgetClass.LoadSynchronous();

	ClearOverlay();

	UWidgetController* WidgetController = UWidgetController::MakeWidgetController(
		OwningPlayerController,
		OverlayControllerClass,
		ObservedActor
	);

	OverlayWidget = CreateWidget<UControllableUserWidget>(OwningPlayerController, WidgetClass);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastValues();

	OverlayWidget->AddToViewport();
}

void UGRHUDOverlayComponent::ClearOverlay()
{
	if (IsValid(OverlayWidget))
		OverlayWidget->RemoveFromParent();

	OverlayController = nullptr;
	OverlayWidget = nullptr;
}
