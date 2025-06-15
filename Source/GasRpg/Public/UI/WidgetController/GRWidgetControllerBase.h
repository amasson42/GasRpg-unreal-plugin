// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController.h"
#include "GRWidgetControllerBase.generated.h"


class AGRCharacterBase;
class AGRPlayerState;
class UGRAbilitySystemComponent;
class UGRVitalAttributeSet;

/**
 * 
 */
UCLASS()
class GASRPG_API UGRWidgetControllerBase : public UWidgetController
{
	GENERATED_BODY()

protected:

    virtual void ObservedActorSet() override;


	UFUNCTION(BlueprintCallable, Category = "WidgetController|GasRpg")
	FORCEINLINE AGRCharacterBase* GetGRCharacter() const { return GRCharacter; }
	UFUNCTION(BlueprintCallable, Category = "WidgetController|GasRpg")
	FORCEINLINE AGRPlayerState* GetGRPlayerState() const { return GRPlayerState; }
	UFUNCTION(BlueprintCallable, Category = "WidgetController|GasRpg")
	FORCEINLINE UGRAbilitySystemComponent* GetGRAbilitySystemComponent() const { return AbilitySystemComponent; }
	UFUNCTION(BlueprintCallable, Category = "WidgetController|GasRpg")
	FORCEINLINE UGRVitalAttributeSet* GetGRAttributeSet() const { return AttributeSet; }


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController|GasRpg")
	TObjectPtr<AGRCharacterBase> GRCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController|GasRpg")
	TObjectPtr<AGRPlayerState> GRPlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController|GasRpg")
	TObjectPtr<UGRAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetController|GasRpg")
	TObjectPtr<UGRVitalAttributeSet> AttributeSet;

};
