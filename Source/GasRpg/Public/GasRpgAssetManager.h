// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GasRpgAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGasRpgAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UGasRpgAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
