// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/GRWidgetControllerBase.h"
#include "GROverlayController.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGROverlayController : public UGRWidgetControllerBase
{
	GENERATED_BODY()

protected:

    virtual void Construct() override;

	virtual void ObservedActorSet() override;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<class UGRVitalAttributesWcc> VitalAttributesWcc;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<class UGREffectInfoTagWcc> EffectInfoTagWcc;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<class UGRAbilitiesInputWcc> AbilitiesInputWcc;

};
