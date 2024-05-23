// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "ScalableFloat.h"
#include "GRCharacterKit.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRCharacterKit : public UDataAsset
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Effects")
	virtual TSubclassOf<UGameplayEffect> GetPrimaryAttributesEffects() const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Effects")
	virtual TSubclassOf<UGameplayEffect> GetSecondaryAttributesEffects() const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Effects")
	virtual void GetBaseEffects(TArray<TSubclassOf<UGameplayEffect>>& Effects, bool bIncludeAttributes = true) const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Abilities")
	virtual void GetStartupAbilities(TArray<FGameplayAbilityGrant>& Abilities) const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Starting")
	virtual void GetOnBeginEffects(TArray<FGameplayEffectParameters>& Effects) const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Abilities")
    virtual void GetStartupAbilitiesForInputs(TMap<FGameplayTag, FGameplayTag>& AbilitiesForInputs) const;

protected:

    /** Base CharacterKit.
     *  Array properties will be added from the parents properties. 
     *  Other properties will be taken from the first valid parent if they are invalid from the child.
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Parent")
    TArray<TObjectPtr<UGRCharacterKit>> Parents;

    /** Base effect that will get created and applied to the character.
     *  It should add to the character its starting values for his primary attributes
     *  The Ability System Component keeps a reference to the effect handles to make it scalable
     * 
     *  ** Overrides parent effects **
     */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Effects|Attributes")
    TSubclassOf<class UGRPrimaryAttributesBaseEffect> PrimaryAttributesEffect;

    /** Base effect that will get created and applied to the character.
     *  It should calculate the secondary attributes
     *  The Ability System Component keeps a reference to the effect handles to make it scalable
     * 
     *  ** Overrides parent effects **
     */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Effects|Attributes")
    TSubclassOf<class UGRSecondaryAttributesBaseEffect> SecondaryAttributesEffect;

    /** Array of effects that will get created and applied to the character.
     *  The Ability System Component keeps a reference to the effect handles to make it scalable
     * 
     *  ** Appends to parent effects **
     */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Effects")
	TArray<TSubclassOf<UGameplayEffect>> BaseEffects;

    /** List of abilities to grant to the character when spawning
     * 
     *  ** Appends to parent abilities **
    */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Abilities")
	TArray<FGameplayAbilityGrant> StartupAbilities;

    /** Effects to apply instantly to the character when spawning
     * 
     *  ** Appends to parent effects **
    */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Starting")
	TArray<FGameplayEffectParameters> OnBeginEffects;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	// TObjectPtr<class UAbilityBook> AbilitiesBook;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Experience")
	// FScalableFloat DeathExperience;

};
