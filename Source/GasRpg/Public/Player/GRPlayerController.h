// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTags.h"
#include "GRPlayerController.generated.h"


class UGRAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GASRPG_API AGRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

    AGRPlayerController();


	// TODO: Use event observing to extract this from the controller to its own component
	/** Floating Damages */
	UFUNCTION(Client, Reliable)
	void Client_ShowFloatingDamages(const FFloatingDamage& FloatingDamage);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowFloatingDamages(const FFloatingDamage& FloatingDamage);

protected:

    virtual void BeginPlay() override;

	virtual void AcknowledgePossession(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	UGRAbilitySystemComponent* GetASC();

	UGRAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UGRInputConfig> AbilityInputConfig;

private:

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

};
