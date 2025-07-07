// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GRPlayerController.h"
#include "Player/GRPlayerControllerFloatingDamagesComponent.h"
#include "Player/GRPlayerControllerComponent.h"


AGRPlayerController::AGRPlayerController()
{
    bReplicates = true;

    FloatingDamagesComponent = CreateDefaultSubobject<UGRPlayerControllerFloatingDamagesComponent>(TEXT("FloatingDamagesComponent"));
    GasRpgControllerComponent = CreateDefaultSubobject<UGRPlayerControllerComponent>(TEXT("GasRpgControllerComponent"));
}

void AGRPlayerController::AcknowledgePossession(APawn* aPawn)
{
    if (IsValid(GasRpgControllerComponent))
        GasRpgControllerComponent->AcknowledgePossession(aPawn);
}

void AGRPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (IsValid(GasRpgControllerComponent))
        GasRpgControllerComponent->SetupInputComponent();
}
