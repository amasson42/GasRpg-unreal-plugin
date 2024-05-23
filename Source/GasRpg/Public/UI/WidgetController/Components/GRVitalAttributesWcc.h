// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "AbilitySystem/GRMainAttributeList.h"
#include "GRVitalAttributesWcc.generated.h"


class UGRAbilitySystemComponent;
class UGRMainAttributeSet;


/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRVitalAttributesWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()


public:

    UFUNCTION(BlueprintCallable, category = "Initialize")
    void Initialize(UGRAbilitySystemComponent* ASC, UGRMainAttributeSet* AS);

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);

    /* [MainAttributeListBoilerplate] Vital attributes listed */
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnHealthChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnMaxHealthChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnManaChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnMaxManaChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnStaminaChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnMaxStaminaChanged;


    UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
    bool IsHealthRelevant() const;

    UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
    bool IsManaRelevant() const;

    UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
    bool IsStaminaRelevant() const;

protected:

    UPROPERTY()
    TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UGRMainAttributeSet> AttributeSet;

};
