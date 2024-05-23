// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GRHUD.generated.h"

class UOverlayController;
class UControllableUserWidget;

/**
 * The base class for HUD
 * It will create an overlay widget automatically with the specified class when
 * the player possess a new character.
 */
UCLASS()
class GASRPG_API AGRHUD : public AHUD
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Overlay|Widget")
    UControllableUserWidget* GetOverlayWidget() const { return OverlayWidget; }

    UFUNCTION(BlueprintCallable, Category = "Overlay|Controller")
	UGROverlayController* GetOverlayController();

	virtual void InitOverlay();

	virtual void ClearOverlay();

protected:

	AActor* GetActorToObserve() const;


	UPROPERTY()
	TObjectPtr<UControllableUserWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay|Widget")
	TSubclassOf<UControllableUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UGROverlayController> OverlayController;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay|Controller")
	TSubclassOf<UGROverlayController> OverlayControllerClass;

};
