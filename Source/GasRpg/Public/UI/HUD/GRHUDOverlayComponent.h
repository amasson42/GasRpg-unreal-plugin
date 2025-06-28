// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GRHUDOverlayComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASRPG_API UGRHUDOverlayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Overlay|Widget")
	UControllableUserWidget* GetOverlayWidget() const { return OverlayWidget; }

	UFUNCTION(BlueprintCallable, Category = "Overlay|Controller")
	UWidgetController* GetOverlayController() const { return OverlayController; }

	UFUNCTION(BlueprintCallable, Category = "Overlay|HUD")
	void InitOverlay(APlayerController* OwningPlayerController, AActor* ObservedActor);

	UFUNCTION(BlueprintCallable, Category = "Overlay|HUD")
	void ClearOverlay();

protected:

	UPROPERTY()
	TObjectPtr<UControllableUserWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay|Widget")
	TSoftClassPtr<UControllableUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UWidgetController> OverlayController;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay|Controller")
	TSubclassOf<UWidgetController> OverlayControllerClass;

};
