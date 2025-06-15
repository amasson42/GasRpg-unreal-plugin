// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GRInputConfig.generated.h"

class UInputAction;


USTRUCT(BlueprintType)
struct FAbilityInputTagAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Action = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag Tag = FGameplayTag();

};


/**
 * 
 */
UCLASS()
class GASRPG_API UGRInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FAbilityInputTagAction> AbilityInputTagActions;
};
