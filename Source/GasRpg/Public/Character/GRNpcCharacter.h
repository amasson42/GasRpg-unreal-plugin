// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GRCharacterBase.h"
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


	/** Combat Interface */

	// virtual int32 GetPlayerLevel_Implementation() const override { return Level; }
	// virtual void SetCombatTarget_Implementation(USceneComponent *NewCombatTarget) override { CombatTarget = NewCombatTarget; }
	// virtual USceneComponent* GetCombatTarget_Implementation() const override { return CombatTarget; }

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Default")
	// int32 Level = 1;

	// UPROPERTY()
	// TObjectPtr<USceneComponent> CombatTarget;
};
