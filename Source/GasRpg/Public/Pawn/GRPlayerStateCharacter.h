// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/GRCharacterBase.h"
#include "GRPlayerStateCharacter.generated.h"

/**
 * GRPlayerStateCharacter is a base class for a character that is playable.
 * They do not initialize their own gameplay ability component but instead look for one in their player state.
 */
UCLASS()
class GASRPG_API AGRPlayerStateCharacter : public AGRCharacterBase
{
	GENERATED_BODY()

public:

    AGRPlayerStateCharacter();


    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;


private:

    virtual void InitAbilitySystem() override;

};
