// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "GameplayTags.h"
#include "GRMainAttributeSetWcc.generated.h"


class UGRAbilitySystemComponent;
class UGRAttributeSet;


/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGRMainAttributeSetWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, category = "Initialize")
	void Initialize(UGRAbilitySystemComponent* ASC, UGRMainAttributeSet* AS);

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeSignature, const FGameplayTag&, AttributeTag, float, NewValue);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnAttributeChange;

protected:

	UPROPERTY()
	TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UGRMainAttributeSet> AttributeSet;

};
