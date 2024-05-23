// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "GameplayTagContainer.h"
#include "GRAbilitiesStatusWcc.generated.h"


class UGRAbilitySystemComponent;

/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRAbilitiesStatusWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()

public:



    UFUNCTION(BlueprintCallable, category = "Initialize")
    void Initialize(UGRAbilitySystemComponent* ASC);

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityStatusUpdatedSignature, const FGameplayTag&, AbilityID, const FGameplayTag&, Status, int32, Level);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStatusRemovedSignature, const FGameplayTag&, AbilityID);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Abilities")
    FOnAbilityStatusUpdatedSignature OnAbilityStatusUpdated;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Abilities")
	FOnAbilityStatusRemovedSignature OnAbilityStatusRemoved;

    // UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "GAS|Abilities")
    // void GetAbilityBookCategories(TSet<FName>& Names) const;

    // UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "GAS|Abilities")
    // void GetAllAbilitiesInformations(TArray<FGRAbilityInfo>& AbilitiesInfo) const;


protected:

    UPROPERTY()
    TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;


private:

    UFUNCTION() void OnAbilitySpecChange(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec);
    UFUNCTION() void OnAbilitySpecRemoving(UGRAbilitySystemComponent* ASC, const FGameplayAbilitySpec& AbilitySpec);

};
