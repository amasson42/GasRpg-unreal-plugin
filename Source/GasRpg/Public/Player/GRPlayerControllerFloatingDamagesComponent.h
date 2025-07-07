// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "GRPlayerControllerFloatingDamagesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASRPG_API UGRPlayerControllerFloatingDamagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGRPlayerControllerFloatingDamagesComponent();

	APlayerController* GetPlayerController();

	/** Floating Damages */
	UFUNCTION(Client, Reliable)
	void Client_ShowFloatingDamages(const FFloatingDamage& FloatingDamage);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFloatingDamagesDelegate, UGRPlayerControllerFloatingDamagesComponent*, ControllerComponent, const FFloatingDamage&, FloatingDamages);

	UPROPERTY(BlueprintAssignable)
	FOnFloatingDamagesDelegate OnFloatingDamagesDelegate;

};
