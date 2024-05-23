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

    /** Effect Interception */

	// UFUNCTION(BlueprintCallable, Category = "Interceptor")
	// void AddGameplayEffectInterceptor(UObject* Interceptor);

	// UFUNCTION(BlueprintCallable, Category = "Interceptor")
	// void RemoveGameplayEffectInterceptor(UObject* Interceptor);


    /** Gameplay Ability */

    DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilitySpecChangeSignature, UGRAbilitySystemComponent*, const FGameplayAbilitySpec&)
    DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilitySpecRemovingSignature, UGRAbilitySystemComponent*, const FGameplayAbilitySpec&)

	FAbilitySpecChangeSignature OnAbilitySpecChange;
	FAbilitySpecRemovingSignature OnAbilitySpecRemoving;

	void GrantAbility(const FGameplayAbilityGrant& Ability);
	void GrantStartupAbilities(const TArray<FGameplayAbilityGrant>& Abilities);

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

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

    DECLARE_DELEGATE_OneParam(FForEachAbilityDelegate, const FGameplayAbilitySpec&)

    void ForEachAbilityDelegate(const FForEachAbilityDelegate& Delegate);
	void ForEachAbilityLambda(std::function<void (FGameplayAbilitySpec&)> Func);

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


    /** Attribute Set */

	/** Attributes Modifications */
	// void AddAttributePoints(float Count, const FGameplayTag& AttributeTag);

protected:

    /** Initialization */

	UFUNCTION()
	void AbilitySystemInitDone();

    /** Ability */

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

	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey = FPredictionKey()) override;

	UFUNCTION(Client, Reliable)
	void Client_OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);

    // UPROPERTY()
    // TMap<FGameplayTag, FGameplayAbilitySpec*> AbilitiesInputsMap;

	// UPROPERTY()
	// TArray<TObjectPtr<UObject>> EffectInterceptors;

	UPROPERTY(BlueprintReadOnly, Category = "Base Effects")
	TArray<FActiveGameplayEffectHandle> BaseEffectsHandles;

    UPROPERTY(BlueprintReadOnly, Category = "Base Effects")
    float BaseEffectsLevel = 1.0f;

    friend class AGRCharacterBase;

private:

};
