// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GRAbilitySystemTypes.h"
#include "GRAbilitySystemLibrary.generated.h"


/**
 * 
 */
UCLASS()
class GASRPG_API UGRAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** GameplayEffects */

	UFUNCTION(BlueprintCallable, Category = "GRAbilitySystemLibrary|Effects")
	static FActiveGameplayEffectHandle ApplyGameplayEffectWithParameters(const FGameplayEffectParameters& EffectParams, UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Effects")
	static bool CheckGameplayEffectSpecHasTag(const FGameplayEffectSpec& EffectSpec, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Effects")
	static void GetContextFromGameplayEffectSpec(const FGameplayEffectSpec& EffectSpec, FGameplayEffectContextHandle& Context);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Effects")
	static void ExtractPropertiesFromGameplayEffectContextHandle(const FGameplayEffectContextHandle& Context, FEffectProperties& Properties);

	UFUNCTION(BlueprintPure, Category = "GRAbilitySystemLibrary|Effect Context")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "GRAbilitySystemLibrary|Effect Context")
	static void SetIsBlockedHit(UPARAM(Ref) FGameplayEffectContextHandle& EffectContextHandle, bool bNewIsBlockedHit);

	UFUNCTION(BlueprintPure, Category = "GRAbilitySystemLibrary|Effect Context")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "GRAbilitySystemLibrary|Effect Context")
	static void SetIsCriticalHit(UPARAM(Ref) FGameplayEffectContextHandle& EffectContextHandle, bool bNewIsCriticalHit);

	UFUNCTION(BlueprintPure, Category = "GRAbilitySystemLibrary|Effect Context")
	static FVector GetHitImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "GRAbilitySystemLibrary|Effect Context")
	static void SetHitImpulse(UPARAM(Ref) FGameplayEffectContextHandle& EffectContextHandle, FVector NewHitImpulse);

    UFUNCTION(BlueprintPure, Category = "GRAbilitySystemLibrary|Effect|Modifiers")
    static void GetGameplayEffectModAtLevel(TSubclassOf<UGameplayEffect> EffectClass, float Level, TMap<FString, float> &Attributes);

    /** GameplayTags */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|GameplayTags")
	static FGameplayTag GetFirstMatchingTagFromTagContainer(const FGameplayTagContainer& TagContainer, FGameplayTag MatchTag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|GameplayTags")
	static void GetMatchingTagsFromTagContainer(const FGameplayTagContainer& TagContainer, FGameplayTag MatchTag, FGameplayTagContainer& MatchingTags);

	UFUNCTION(BlueprintCallable, Category = "GRAbilitySystemLibrary|GameplayTags")
	static bool RemoveMatchingTagsFromTagContainer(FGameplayTagContainer& TagContainer, FGameplayTag MatchTag);


	/** Abilities */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Abilities")
	static FGameplayTag GetAbilityIdFromAbilityClass(TSubclassOf<UGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Abilities")
	static FGameplayTag GetTypeTagFromAbilityClass(TSubclassOf<UGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Abilities")
	static FGameplayTag GetCooldownTagFromAbilityClass(TSubclassOf<UGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Abilities")
	static void GetAbilityCostAtLevel(TSubclassOf<UGameplayAbility> AbilityClass, float Level, TMap<FString, float>& Costs);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|Abilities")
	static float GetAbilityCooldownTimeAtLevel(TSubclassOf<UGameplayAbility> AbilityClass, float Level);


    /** General */

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|General")
	static void MakeTargetDataHandleWithSingleHitResult(const FHitResult& HitResult, FGameplayAbilityTargetDataHandle& Handle);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|General")
	static void MakeTargetDataHandleWithSingleVector(const FVector& Vector, FGameplayAbilityTargetDataHandle& Handle);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GRAbilitySystemLibrary|General")
    static void GetVectorFromTargetData(const FGameplayAbilityTargetDataHandle& Handle, const int Index, FVector& Vector);

};
