// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GRCharacterBase.h"
#include "GRPlayerCharacter.generated.h"

/**
 * GRPlayerCharacter is the base class for all characters that are playable.
 * They do not initialize their own gameplay ability component and use the
 * one from their player state.
 * 
 * @see AGRCharacterBase
 */
UCLASS()
class GASRPG_API AGRPlayerCharacter : public AGRCharacterBase
{
	GENERATED_BODY()

public:

    AGRPlayerCharacter();


    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;


private:

    virtual void InitAbilitySystem() override;


	// /** Combat Interface */
	// virtual int32 GetPlayerLevel_Implementation() const override;

	// /** Player Interface */
	// virtual class ULevelingExperienceComponent* GetLevelingExperienceComponent_Implementation() const override;

};
