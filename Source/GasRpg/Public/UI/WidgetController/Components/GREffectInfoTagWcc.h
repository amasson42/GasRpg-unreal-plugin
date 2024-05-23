// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "GameplayTagContainer.h"
#include "GREffectInfoTagWcc.generated.h"


class UGRAbilitySystemComponent;


/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGREffectInfoTagWcc : public UWidgetControllerComponent
{
	GENERATED_BODY()

public:


    UFUNCTION(BlueprintCallable, category = "Initialize")
	void Initialize(UGRAbilitySystemComponent* ASC);

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewEffectInfoTagSignature, const FGameplayTag&, EffectInfoTag);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Effect Event Tag")
    FOnNewEffectInfoTagSignature OnNewEffectInfoTag;

protected:

	UPROPERTY()
	TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

};
