// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/Components/AAbilitySystemWidgetComponent.h"
#include "GRVitalAttributesWcc.generated.h"

class UGRVitalAttributeSet;

/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRVitalAttributesWcc : public UAAbilitySystemWidgetComponent
{
	GENERATED_BODY()


public:

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnHealthChanged;
    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
    FOnAttributeChangeSignature OnMaxHealthChanged;


protected:

	virtual void SetObservedActor(AActor* Actor) override;

    UPROPERTY()
    TObjectPtr<UGRVitalAttributeSet> AttributeSet;

};
