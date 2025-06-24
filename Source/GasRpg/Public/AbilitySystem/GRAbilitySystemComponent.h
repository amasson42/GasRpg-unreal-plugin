// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "GRAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGRAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

    /** Gameplay Effect */

    DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer&)
    
    /** Relevant on client. Broadcast received asset tags from gameplay effects */
	FEffectAssetTagsSignature OnEffectAssetTags;

    void AddBaseEffect(const TSubclassOf<UGameplayEffect>& EffectClass);

    UFUNCTION(BlueprintCallable)
    void SetBaseEffectsLevel(float Level);


    /** Gameplay Ability */

    DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilitySpecChangeSignature, UGRAbilitySystemComponent*, const FGameplayAbilitySpec&)
    DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilitySpecRemovingSignature, UGRAbilitySystemComponent*, const FGameplayAbilitySpec&)

	FAbilitySpecChangeSignature OnAbilitySpecChange;
	FAbilitySpecRemovingSignature OnAbilitySpecRemoving;

    UFUNCTION(BlueprintCallable, Category = "Ability")
	FGameplayAbilitySpecHandle GrantAbility(const FGameplayAbilityGrant& Ability);

	/** Ability Level */
	void SetLevelForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, int32 NewLevel);
	void AddLevelForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, int32 AddLevel);

	/** Managing Tags */
	FGameplayAbilitySpec* GetAbilitySpecForAbilityIDTag(const FGameplayTag& AbilityIDTag);
	void GetAbilitySpecsForInputTag(const FGameplayTag& InputTag, TArray<FGameplayAbilitySpec*>& AbilitySpecs);

	/** Manage Status Tags */
	bool GetStatusTagForAbilityIDTag(const FGameplayTag AbilityIDTag, FGameplayTag& StatusTag);

	/** Manage Input Tags */
	void RemoveInputTagFromAbilitySpec(FGameplayAbilitySpec& AbilitySpec, bool bBroadcastUpdate = true);
	void ClearAbilitiesFromInputTag(const FGameplayTag& InputTag);
	void AssignInputTagToAbilitySpec(const FGameplayTag& InputTag, FGameplayAbilitySpec& AbilitySpec);

    UFUNCTION(BlueprintCallable, Category = "Ability")
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
    UFUNCTION(BlueprintCallable, Category = "Ability")
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
    UFUNCTION(BlueprintCallable, Category = "Ability")
	void AbilityInputTagReleased(const FGameplayTag& InputTag);


	DECLARE_DELEGATE_OneParam(FForEachAbilityDelegate, FGameplayAbilitySpec&)
    void ForEachAbilityDelegate(const FForEachAbilityDelegate& Delegate);
	void ForEachAbilityLambda(TFunction<void (FGameplayAbilitySpec&)> Func);

	/** Ability Tags */
	static bool AbilityHasIDTag(const UGameplayAbility* Ability);
	static FGameplayTag GetAbilityIDTagFromAbility(const UGameplayAbility* Ability);
	static bool AbilitySpecHasInputTag(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec);
	static bool AbilityHasCooldownTag(const UGameplayAbility* Ability);
	static FGameplayTag GetCooldownTagFromAbility(const UGameplayAbility* Ability);
	static bool AbilitySpecHasStatusTag(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusTagFromAbilitySpec(const FGameplayAbilitySpec& AbilitySpec);
	static bool AbilityHasTypeTag(const UGameplayAbility* Ability);
	static FGameplayTag GetTypeTagFromAbility(const UGameplayAbility* Ability);
	/** End Ability Tags */


    /** Initialization */

	UFUNCTION()
	void AbilitySystemInit(UGRAbilityKit* AdditionalKit = nullptr);

protected:
	
	void AddKitBaseEffects(UGRAbilityKit* Kit);
	void AddKitStartupAbilities(UGRAbilityKit* Kit);
	void ApplyKitStartupEffects(UGRAbilityKit* Kit);

    /** Ability */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Kit")
	TObjectPtr<class UGRAbilityKit> AbilityKit;

	bool bStartupAbilitiesGiven = false;

	void UpdateStatusTagForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, bool bBroadcastUpdate = true);

	void SetStatusTagForAbilitySpec(FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& StatusTag, bool bBroadcastUpdate = true);

	UFUNCTION(Client, Reliable)
	void Client_UpdateAbilityStatus(const FGameplayTag& AbilityID, const FGameplayTag& Status, int32 Level);

	void ActivateAbilityIfEquippedPassive(FGameplayAbilitySpec& AbilitySpec);

	virtual void OnRep_ActivateAbilities() override;
	virtual void OnGiveAbility(FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(FGameplayAbilitySpec& Spec) override;


    /** Effects */

	UFUNCTION(Client, Reliable)
	void Client_OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);

    // UPROPERTY()
    // TMap<FGameplayTag, FGameplayAbilitySpec*> AbilitiesInputsMap;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> BaseEffectsHandles;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Effects")
    float BaseEffectsLevel = 1.0f;
};
