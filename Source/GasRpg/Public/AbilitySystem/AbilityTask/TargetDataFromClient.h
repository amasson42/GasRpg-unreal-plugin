// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataFromClient.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GASRPG_API UAbilityTask_TargetDataFromClient : public UAbilityTask
{
	GENERATED_BODY()

public:

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FValidTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoTargetDataSignature);

	UPROPERTY(BlueprintAssignable)
	FValidTargetDataSignature ValidData;
	UPROPERTY(BlueprintAssignable)
	FNoTargetDataSignature NoData;


protected:

    virtual bool AddTargetDataToHandle(FGameplayAbilityTargetDataHandle& Handle)
    {
        return false;
    }

	virtual void Activate() override;

	void SendTargetData();
    void WaitToReceiveTargetData();

    void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);

};
