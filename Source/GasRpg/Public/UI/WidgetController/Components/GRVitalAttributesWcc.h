// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "GRVitalAttributesWcc.generated.h"


class UGRAbilitySystemComponent;
class UGRVitalAttributeSet;


/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRVitalAttributesWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()


public:

    UFUNCTION(BlueprintCallable, category = "Initialize")
    void Initialize(UGRAbilitySystemComponent* ASC, UGRVitalAttributeSet* AS);

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnHealthChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnMaxHealthChanged;


protected:

    UPROPERTY()
    TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UGRVitalAttributeSet> AttributeSet;

};
