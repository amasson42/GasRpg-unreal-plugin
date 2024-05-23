// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "GREffectActor.generated.h"

class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct GASRPG_API FEffectHandleArray
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FActiveGameplayEffectHandle> Handles;
};

UCLASS()
class GASRPG_API AGREffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGREffectActor();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool ApplyEffectsToActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool ApplyEffectsToAbilitySystemComponent(UAbilitySystemComponent* ASC);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    bool ApplyEffectsToHitResult(const FHitResult& HitResult);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    bool ApplyEffectWithParametersToAbilitySystemComponent(const FGameplayEffectParameters& EffectParams, UAbilitySystemComponent* TargetASC);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool RemoveEffectsFromActor(AActor* Actor, bool bInfiniteOnly = false);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool RemoveEffectsFromAbilitySystemComponent(UAbilitySystemComponent* ASC, bool bInfiniteOnly = false);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    bool RemoveAllEffects(bool bInfiniteOnly = false);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))
	TArray<FGameplayEffectParameters> Effects;

	UPROPERTY(BlueprintReadOnly, Category = "Effects")
    TWeakObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TMap<UAbilitySystemComponent*, FEffectHandleArray> ActiveEffectHandles;

};
