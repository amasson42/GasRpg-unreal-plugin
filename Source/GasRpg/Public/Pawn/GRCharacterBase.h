// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactionSystem/Pawn/FactionCharacter.h"
#include "AbilitySystemInterface.h"
#include "Pawn/AnimatableCharacterInterface.h"
#include "Pawn/GasPawnInterface.h"
#include "GameplayTags.h"
#include "GRCharacterBase.generated.h"

class UAbilitySystemComponent;
class UGRAbilityKit;

/**
 * GRCharacterBase is the base character class for every character.
 * It's a direct subclass to the engine Character and add multiple
 * utilities to the base class
 * 
 * @see ACharacter
 */ 
UCLASS(Abstract)
class GASRPG_API AGRCharacterBase : public AFactionCharacter, public IAbilitySystemInterface, public IAnimatableCharacterInterface, public IGasPawnInterface
{
	GENERATED_BODY()

public:

	AGRCharacterBase();

	/** Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** RpgCharacter Interface*/

	virtual FVector GetSocketLocation_Implementation(FGameplayTag SocketTagName) const override;
	virtual USceneComponent* GetSocketComponent_Implementation(FGameplayTag SocketTag) const override;
	virtual FRpgCharacterMontage GetMontage_Implementation(FGameplayTag MontageTag) const override;

	/** Gas Pawn Interface */
	virtual void WithInitializedAbilitySystem(const FWithInitializedAbilitySystemDelegate& Delegate) override;

protected:

	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "RpgCharacter|Montage")
    TMap<FGameplayTag, FRpgCharacterMontageArray> RpgMontages;

	FOnAbilitySystemInitializedDelegate OnAbilitySystemInitialized;

	bool bASCInitialized = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UFUNCTION()
	virtual void InitAbilitySystem(UGRAbilityKit* AdditionalKit = nullptr);

};
