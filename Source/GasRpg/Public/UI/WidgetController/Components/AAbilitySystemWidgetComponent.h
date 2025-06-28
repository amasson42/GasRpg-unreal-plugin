// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllerComponent.h"
#include "AAbilitySystemWidgetComponent.generated.h"

class UGRAbilitySystemComponent;


/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class GASRPG_API UAAbilitySystemWidgetComponent : public UWidgetControllerComponent
{
	GENERATED_BODY()

protected:

	virtual void SetObservedActor(AActor* Actor) override;

	UPROPERTY()
    TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

};
