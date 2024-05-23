// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GREffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"

AGREffectActor::AGREffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
}

void AGREffectActor::BeginPlay()
{
	Super::BeginPlay();

    SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetInstigator());
}

bool AGREffectActor::ApplyEffectsToActor(AActor* Actor)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	return ApplyEffectsToAbilitySystemComponent(ASC);
}

bool AGREffectActor::ApplyEffectsToHitResult(const FHitResult& HitResult)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());

    if (!IsValid(TargetASC))
    {
        return false;
    }

	bool bEffectApplied = false;

	for (FGameplayEffectParameters Effect : Effects)
	{
        Effect.HitImpulse = GetVelocity();
        Effect.HitCollision = HitResult;
		bEffectApplied |= ApplyEffectWithParametersToAbilitySystemComponent(Effect, TargetASC);
	}

	return bEffectApplied;
}

bool AGREffectActor::ApplyEffectsToAbilitySystemComponent(UAbilitySystemComponent* ASC)
{
	if (!IsValid(ASC))
		return false;

	bool bEffectApplied = false;

	for (FGameplayEffectParameters Effect : Effects)
	{
		bEffectApplied |= ApplyEffectWithParametersToAbilitySystemComponent(Effect, ASC);
	}

	return bEffectApplied;
}

bool AGREffectActor::ApplyEffectWithParametersToAbilitySystemComponent(const FGameplayEffectParameters& EffectParams, UAbilitySystemComponent* TargetASC)
{
    if (!IsValid(TargetASC))
		return false;

    if (!IsValid(EffectParams.Class))
    {
        return false;
    }

	FActiveGameplayEffectHandle ActiveEffectHandle = UGRAbilitySystemLibrary::ApplyGameplayEffectWithParameters(EffectParams, SourceASC.Get(), TargetASC);

	bool bIsInstant = EffectParams.Class->GetDefaultObject<UGameplayEffect>()->DurationPolicy == EGameplayEffectDurationType::Instant;

	if (!bIsInstant)
	{
		if (ActiveEffectHandles.Contains(TargetASC))
        {
            ActiveEffectHandles[TargetASC].Handles.Add(ActiveEffectHandle);
        }
        else
        {
            FEffectHandleArray HandleArray;
            HandleArray.Handles.Add(ActiveEffectHandle);
            ActiveEffectHandles.Add(TargetASC, HandleArray);
        }
    }

	return true;
}

bool AGREffectActor::RemoveEffectsFromActor(AActor* Actor, bool bInfiniteOnly)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	return RemoveEffectsFromAbilitySystemComponent(ASC, bInfiniteOnly);
}

bool _IsActiveHandleInfinite(UAbilitySystemComponent* ASC, const FActiveGameplayEffectHandle& Handle)
{
    if (const FActiveGameplayEffect* ActiveEffect = ASC->GetActiveGameplayEffect(Handle))
    {
        if (const UGameplayEffect* GameplayEffect = ActiveEffect->Spec.Def)
        {
            return GameplayEffect->DurationPolicy == EGameplayEffectDurationType::Infinite;
        }
    }
    return false;
}

bool AGREffectActor::RemoveEffectsFromAbilitySystemComponent(UAbilitySystemComponent* ASC, bool bInfiniteOnly)
{
	if (!IsValid(ASC))
		return false;

	bool bRemovedEffect = false;

	FEffectHandleArray ActiveHandles;
	if (ActiveEffectHandles.RemoveAndCopyValue(ASC, ActiveHandles))
	{
		for (const FActiveGameplayEffectHandle& Handle : ActiveHandles.Handles)
		{
            bool bShouldRemove = true;

            if (bInfiniteOnly)
            {
                bShouldRemove = _IsActiveHandleInfinite(ASC, Handle);
            }

            if (bShouldRemove)
            {
			    bRemovedEffect |= ASC->RemoveActiveGameplayEffect(Handle, 1);
            }
		}
	}

	return bRemovedEffect;
}

bool AGREffectActor::RemoveAllEffects(bool bInfiniteOnly)
{
    bool bRemovedEffect = false;

    for (const TPair<UAbilitySystemComponent*, FEffectHandleArray>& AscEffectHandles : ActiveEffectHandles)
    {
        UAbilitySystemComponent* ASC = AscEffectHandles.Key;
        const TArray<FActiveGameplayEffectHandle>& Handles = AscEffectHandles.Value.Handles;

        for (const FActiveGameplayEffectHandle& Handle : Handles)
        {
            bool bShouldRemove = true;

            if (bInfiniteOnly)
            {
                bShouldRemove = _IsActiveHandleInfinite(ASC, Handle);
            }

            if (bShouldRemove)
            {
                bRemovedEffect |= ASC->RemoveActiveGameplayEffect(Handle, 1);
            }
        }
    }

    ActiveEffectHandles.Reset();

    return bRemovedEffect;
}
