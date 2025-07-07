// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactionSystem/FactionPlayerController.h"
#include "GRPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class GASRPG_API AGRPlayerController : public AFactionPlayerController
{
	GENERATED_BODY()

public:

    AGRPlayerController();

protected:

	virtual void AcknowledgePossession(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(VisibleAnywhere, Category = "GasRpg")
	class UGRPlayerControllerFloatingDamagesComponent* FloatingDamagesComponent;

	UPROPERTY(VisibleAnywhere, Category = "GasRpg")
	class UGRPlayerControllerComponent* GasRpgControllerComponent;

};
