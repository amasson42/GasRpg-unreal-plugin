// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GasPawnInterface.generated.h"


class UAbilitySystemComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UGasPawnInterface : public UInterface
{
	GENERATED_BODY()
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FWithInitializedAbilitySystemDelegate, UAbilitySystemComponent*, AbilitySystemComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilitySystemInitializedDelegate, UAbilitySystemComponent*, AbilitySystemComponent);

/**
 * 
 */
class GASRPG_API IGasPawnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void WithInitializedAbilitySystem(const FWithInitializedAbilitySystemDelegate& Delegate);

};
