// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AbilityTask/TargetDataPawnMovementInput.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"

UAbilityTask_TargetDataPawnMovementInput *UAbilityTask_TargetDataPawnMovementInput::CreateTargetDataPawnMovementInputProxy(UGameplayAbility *OwningAbility)
{
    UAbilityTask_TargetDataPawnMovementInput *MyObj = NewAbilityTask<UAbilityTask_TargetDataPawnMovementInput>(OwningAbility);
    return MyObj;
}

bool UAbilityTask_TargetDataPawnMovementInput::AddTargetDataToHandle(FGameplayAbilityTargetDataHandle &Handle)
{
    AActor *Avatar = Ability->GetCurrentActorInfo()->AvatarActor.Get();

    if (!IsValid(Avatar))
    {
        return false;
    }

    APawn *AvatarPawn = Cast<APawn>(Avatar);
    if (!IsValid(AvatarPawn))
    {
        return false;
    }

    FVector MovementInputVector = AvatarPawn->GetLastMovementInputVector();

    FGameplayAbilityTargetData_Vector *Data = new FGameplayAbilityTargetData_Vector();
    Data->Vector = MovementInputVector;

    Handle.Add(Data);

    return true;
}
