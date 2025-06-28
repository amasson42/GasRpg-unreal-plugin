// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/Components/AAbilitySystemWidgetComponent.h"
#include "GameplayTagContainer.h"
#include "GRAbilitiesStatusWcc.generated.h"


class UGRAbilitySystemComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRAbilitiesStatusWcc : public UAAbilitySystemWidgetComponent
{
	GENERATED_BODY()

public:

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityStatusUpdatedSignature, const FGameplayTag&, AbilityID, const FGameplayTag&, Status, int32, Level);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStatusRemovedSignature, const FGameplayTag&, AbilityID);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Abilities")
    FOnAbilityStatusUpdatedSignature OnAbilityStatusUpdated;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Abilities")
	FOnAbilityStatusRemovedSignature OnAbilityStatusRemoved;

private:

    UFUNCTION() void OnAbilitySpecChange(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec);
    UFUNCTION() void OnAbilitySpecRemoving(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec);

};
