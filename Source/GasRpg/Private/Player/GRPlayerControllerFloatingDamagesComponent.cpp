// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GRPlayerControllerFloatingDamagesComponent.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"


UGRPlayerControllerFloatingDamagesComponent::UGRPlayerControllerFloatingDamagesComponent()
{
    SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UGRPlayerControllerFloatingDamagesComponent::Client_ShowFloatingDamages_Implementation(const FFloatingDamage& FloatingDamage)
{
    OnFloatingDamagesDelegate.Broadcast(this, FloatingDamage);
}
