// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/GRCharacterBase.h"
#include "GRPlayerCharacter.generated.h"

/**
 * GRPlayerCharacter is the base character class for all characters that are not
 * playable. They can initialize their own gameplay ability component and
 * do not rely on any features from a player state or player controller.
 * 
 * @see AGRCharacterBase
 */
UCLASS()
class GASRPG_API AGRPlayerCharacter : public AGRCharacterBase
{
	GENERATED_BODY()

public:

    AGRPlayerCharacter();


protected:

    virtual void BeginPlay() override;

	virtual void InitAbilitySystem(UGRAbilityKit* AbilityKit = nullptr) override;
	
};
