// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "GRPlayerControllerComponent.generated.h"

class UGRAbilitySystemComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASRPG_API UGRPlayerControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGRPlayerControllerComponent();

	virtual void AcknowledgePossession(APawn* aPawn);
	virtual void SetupInputComponent();

	APlayerController* GetPlayerController();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UGRInputConfig> AbilityInputConfig;

	UPROPERTY(BlueprintReadOnly, Category = "Controller")
	APlayerController* PlayerController;

	UPROPERTY()
	UGRAbilitySystemComponent* AbilitySystemComponent;

	void FetchASC();

	void BindAbilityActions();

private:

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
