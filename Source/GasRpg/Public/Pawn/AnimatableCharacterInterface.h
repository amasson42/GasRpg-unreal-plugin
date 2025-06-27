// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "AnimatableCharacterInterface.generated.h"


class UAbilitySystemComponent;


USTRUCT(BlueprintType, Blueprintable)
struct FRpgCharacterMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag EventTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SocketTag = FGameplayTag::EmptyTag;

};

USTRUCT(BlueprintType, Blueprintable)
struct FRpgCharacterMontageArray
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FRpgCharacterMontage> Montages;

};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimatableCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GASRPG_API IAnimatableCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetSocketLocation(FGameplayTag SocketTag) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USceneComponent* GetSocketComponent(FGameplayTag SocketTag) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FRpgCharacterMontage GetMontage(FGameplayTag MontageTag) const;

};
