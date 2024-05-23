// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityTask/TargetDataFromClient.h"
#include "TargetDataUnderMouse.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UAbilityTask_TargetDataUnderMouse : public UAbilityTask_TargetDataFromClient
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
        meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
	static UAbilityTask_TargetDataUnderMouse* CreateTargetDataUnderMouseProxy(UGameplayAbility* OwningAbility, ECollisionChannel TraceChannel);


protected:

    virtual bool AddTargetDataToHandle(FGameplayAbilityTargetDataHandle& Handle) override;

    ECollisionChannel CursorTraceChannel;

};
