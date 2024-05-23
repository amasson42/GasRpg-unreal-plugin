// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "ActiveGameplayEffectHandle.h"
#include "InspectCooldownTask.generated.h"

class UAbilitySystemComponent;
struct FGameplayEffectSpec;


/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "AsyncTask"))
class GASRPG_API UInspectCooldownTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true))
	static UInspectCooldownTask* InspectCooldown(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InCooldownTag);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCooldownChangeSignature, float, TimeRemaining, float, TimeTotal);

	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownEnd;

	UFUNCTION(BlueprintCallable)
	void EndTask();

	UFUNCTION(BlueprintCallable)
	void BroadcastEffectCooldownTime();

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CooldownTag;

	void CooldownTagChanged(const FGameplayTag ChangedTag, int32 NewCount);
	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle);

	bool EffectHasCooldownTag(const FGameplayEffectSpec& EffectSpec);
};
