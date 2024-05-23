// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouseProxy(UGameplayAbility* OwningAbility, ECollisionChannel TraceChannel)
{
    UAbilityTask_TargetDataUnderMouse* MyObj = NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwningAbility);
    MyObj->CursorTraceChannel = TraceChannel;
    return MyObj;
}


bool UAbilityTask_TargetDataUnderMouse::AddTargetDataToHandle(FGameplayAbilityTargetDataHandle& Handle)
{
    APlayerController *PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

    if (!PC)
    {
        return false;
    }

    FHitResult CursorHit;
    if (!PC->GetHitResultUnderCursor(CursorTraceChannel, false, CursorHit))
    {
        return false;
    }

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;

    Handle.Add(Data);

    return true;
}
