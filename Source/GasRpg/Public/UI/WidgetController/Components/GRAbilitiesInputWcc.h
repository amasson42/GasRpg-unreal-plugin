// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "GameplayTagContainer.h"
#include "GRAbilitiesInputWcc.generated.h"

class UGRAbilitySystemComponent;


/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRAbilitiesInputWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, category = "Initialize")
    void Initialize(UGRAbilitySystemComponent* ASC);

	virtual void BroadcastValues() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityInputChangeSignature, const FGameplayTag&, InputTag, const FGameplayTag&, AbilityID);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityInputRemovedSignature, const FGameplayTag&, InputTag);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Abilities")
	FOnAbilityInputChangeSignature OnAbilityInputChange;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Abilities")
	FOnAbilityInputRemovedSignature OnAbilityInputRemoved;


protected:

	virtual void BindCallbacksToDependencies() override;

    UPROPERTY()
    TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;


private:

    UFUNCTION() void OnAbilitySpecChange(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec);
    UFUNCTION() void OnAbilitySpecRemoving(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec);

    UPROPERTY()
    TSet<FGameplayTag> AbilitiesInputTags;

};
