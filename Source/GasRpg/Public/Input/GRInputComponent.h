// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GRInputConfig.h"
#include "GRInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGRInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	template<class UserClass, typename PressedFuncType, typename ReleaseFuncType, typename HeldFuncType>
	void BindAbilityActions(const UGRInputConfig* InputConfig,
		UserClass* BindObject, PressedFuncType PressedFunc,
		ReleaseFuncType ReleaseFunc, HeldFuncType HeldFunc)
    {
        check(InputConfig)

        for (const FAbilityInputTagAction& InputTagAction : InputConfig->AbilityInputTagActions)
        {
            const FGameplayTag& InputTag = InputTagAction.Tag;
            const UInputAction* InputAction = InputTagAction.Action;

            if (!(IsValid(InputAction) && InputTag.IsValid()))
                continue;

            if (PressedFunc)
                BindAction(InputAction, ETriggerEvent::Started, BindObject, PressedFunc, InputTag);
            if (ReleaseFunc)
                BindAction(InputAction, ETriggerEvent::Completed, BindObject, ReleaseFunc, InputTag);
            if (HeldFunc)
                BindAction(InputAction, ETriggerEvent::Triggered, BindObject, HeldFunc, InputTag);
        }

    }

};
