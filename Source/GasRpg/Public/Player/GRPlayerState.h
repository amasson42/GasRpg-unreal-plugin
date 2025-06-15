// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GRPlayerState.generated.h"


class UGRAbilitySystemComponent;
class UGRVitalAttributeSet;

/**
 * 
 */
UCLASS()
class GASRPG_API AGRPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

    AGRPlayerState();


    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UGRVitalAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:

    UPROPERTY()
    TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UGRVitalAttributeSet> AttributeSet;


};
