// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/Components/AAbilitySystemWidgetComponent.h"
#include "GameplayTagContainer.h"
#include "GREffectInfoTagWcc.generated.h"



/**
 * 
 */
UCLASS(BlueprintType)
class GASRPG_API UGREffectInfoTagWcc : public UAAbilitySystemWidgetComponent
{
	GENERATED_BODY()

public:

	virtual void BroadcastValues() override;
	virtual void BindCallbacksToDependencies() override;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewEffectInfoTagSignature, const FGameplayTag&, EffectInfoTag);

    UPROPERTY(BlueprintAssignable, Category = "GAS|Effect Event Tag")
    FOnNewEffectInfoTagSignature OnNewEffectInfoTag;

};
