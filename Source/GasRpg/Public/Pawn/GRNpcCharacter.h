// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/GRCharacterBase.h"
#include "GRNpcCharacter.generated.h"

/**
 * GRNpcCharacter is a base character class for characters that are not playable.
 * They initialize their own gameplay ability component
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

	virtual void InitAbilitySystem(UGRAbilityKit* AbilityKit = nullptr) override;
	
};
