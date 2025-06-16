// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "GRAbilityKit.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRAbilityKit : public UDataAsset
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Effects")
	virtual void GetBaseEffects(TArray<TSubclassOf<UGameplayEffect>>& Effects) const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Base|Abilities")
	virtual void GetStartupAbilities(TArray<FGameplayAbilityGrant>& Abilities) const;

    UFUNCTION(BlueprintCallable, Category = "Character Kit|Starting")
	virtual void GetStartupEffects(TArray<FGameplayEffectParameters>& Effects) const;

protected:

	void GetBaseEffects(TMap<FGameplayTag, TSubclassOf<UGameplayEffect>>& OverridableEffects, TArray<TSubclassOf<UGameplayEffect>> &Effects) const;

	/** Base CharacterKit.
     *  Array properties will be added from the parents properties. 
     *  Other properties will be taken from the first valid parent if they are invalid from the child.
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Parent")
    TArray<TObjectPtr<UGRAbilityKit>> Parents;

	/** Base effect that will get created and applied to the character.
	 *  It should calculate the secondary attributes
	 *  The Ability System Component keeps a reference to the effect handles to make it scalable
	 * 
	 *  ** Overrides parent effects with the same identifier **
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Kit|Base|Effects")
    TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> OverridableBaseEffects;

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

};
