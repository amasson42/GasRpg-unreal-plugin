// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/GRInputConfig.h"


const UInputAction* UGRInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
    for (const FAbilityInputTagAction& InputTagAction : AbilityInputTagActions)
    {
        if (InputTagAction.Tag.MatchesTagExact(InputTag))
        {
            return InputTagAction.Action;
        }
    }
    return nullptr;
}
