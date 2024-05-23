// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityTask/TargetDataFromClient.h"
#include "TargetDataPawnMovementInput.generated.h"

/**
 *
 */
UCLASS()
class GASRPG_API UAbilityTask_TargetDataPawnMovementInput : public UAbilityTask_TargetDataFromClient
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",
              meta = (DisplayName = "TargetDataPawnMovementInput", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
    static UAbilityTask_TargetDataPawnMovementInput *CreateTargetDataPawnMovementInputProxy(UGameplayAbility *OwningAbility);

protected:
    virtual bool AddTargetDataToHandle(FGameplayAbilityTargetDataHandle &Handle) override;
};
