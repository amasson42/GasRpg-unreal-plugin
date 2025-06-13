// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayTagContainer.h"
#include "GRAbilitySystemTypes.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

USTRUCT(BlueprintType, Blueprintable)
struct GASRPG_API FGameplayEffectParameters
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> Class = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FGameplayTag, float> SetByCallerMagnitudes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector HitImpulse = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite)
    FHitResult HitCollision;

    UPROPERTY(BlueprintReadWrite)
    TObjectPtr<UGameplayAbility> SourceAbility;
};

USTRUCT(BlueprintType, Blueprintable)
struct GASRPG_API FGameplayAbilityGrant
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayAbility> Class = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag InputTag = FGameplayTag::EmptyTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ActiveOnGranted = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct GASRPG_API FEffectProperties
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayEffectContextHandle EffectContextHandle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> SourceAvatarActor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AController> SourceController = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> TargetAvatarActor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AController> TargetController = nullptr;
};

USTRUCT(BlueprintType)
struct GASRPG_API FFloatingDamage
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TWeakObjectPtr<AActor> Source;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TWeakObjectPtr<AActor> Target;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damages = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer Tags;
};

USTRUCT(BlueprintType)
struct GASRPG_API FGRGameplayEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

public:
    /** Returns the actual struct used for serialization, subclasses must override this! */
    virtual UScriptStruct *GetScriptStruct() const
    {
        return StaticStruct();
    }

    /** Creates a copy of this context, used to duplicate for later modifications */
    virtual FGRGameplayEffectContext* Duplicate() const;

    /** Custom serialization, subclasses must override this */
    virtual bool NetSerialize(FArchive &Ar, class UPackageMap *Map, bool &bOutSuccess);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    bool bIsBlockedHit = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    bool bIsCriticalHit = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FVector HitImpulse = FVector::ZeroVector;
};

template <>
struct TStructOpsTypeTraits<FGRGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FGRGameplayEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
    };
};

USTRUCT(BlueprintType)
struct GASRPG_API FGameplayAbilityTargetData_Vector : public FGameplayAbilityTargetData
{
    GENERATED_BODY()
public:
    FGameplayAbilityTargetData_Vector()
        : FGameplayAbilityTargetData(),
          Vector(FVector::ZeroVector)
    {
    }

    UPROPERTY()
    FVector Vector;

    virtual UScriptStruct *GetScriptStruct() const override
    {
        return FGameplayAbilityTargetData_Vector::StaticStruct();
    }

    bool NetSerialize(FArchive &Ar, class UPackageMap *Map, bool &bOutSuccess)
    {
        Vector.NetSerialize(Ar, Map, bOutSuccess);
        bOutSuccess = true;
        return true;
    }
};

template <>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_Vector> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_Vector>
{
    enum
    {
        WithNetSerializer = true
    };
};
