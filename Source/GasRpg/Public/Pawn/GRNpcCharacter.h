// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/GRCharacterBase.h"
#include "GRNpcCharacter.generated.h"

/**
 * GRNpcCharacter is the base character class for all characters that are not
 * playable. They can initialize their own gameplay ability component and
 * do not rely on any features from a player state or player controller.
 * 
 * @see AGRCharacterBase
 */
UCLASS()
class GASRPG_API AGRNpcCharacter : public AGRCharacterBase
{
	GENERATED_BODY()

public:

    AGRNpcCharacter();


protected:

    virtual void BeginPlay() override;

	virtual void InitAbilitySystem() override;
	
};
