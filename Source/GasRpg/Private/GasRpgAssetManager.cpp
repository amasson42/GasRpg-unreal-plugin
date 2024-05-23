// Fill out your copyright notice in the Description page of Project Settings.


#include "GasRpgAssetManager.h"
#include "GasRpgGameplayTags.h"
#include "AbilitySystemGlobals.h"

UGasRpgAssetManager& UGasRpgAssetManager::Get()
{
    check(GEngine);
    return *Cast<UGasRpgAssetManager>(GEngine->AssetManager);
}

void UGasRpgAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    FGRGameplayTags::InitializeNativeGameplayTags();
    UAbilitySystemGlobals::Get().InitGlobalData();
}
