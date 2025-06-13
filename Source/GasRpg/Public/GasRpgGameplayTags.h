
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/GRMainAttributeList.h"

/**
 * GasRpgGameplayTags
 * 
 * Singleton containing gameplay tags
*/
struct FGRGameplayTags
{
public:
    static const FGRGameplayTags& Get() { return GameplayTags; }
    static void InitializeNativeGameplayTags();

    #define __GASRPG_GAMEPLAYTAGS_SINGLETON_PROPERTYDECLARATION__(AttributeName, CategoryName) FGameplayTag Attributes_##CategoryName##_##AttributeName;

    FOREACH_ATTRIBUTE_All(__GASRPG_GAMEPLAYTAGS_SINGLETON_PROPERTYDECLARATION__)

    FGameplayTag InputTag;

    FGameplayTag Event;
    FGameplayTag Event_AbilitySystem_DamageApplied;
    FGameplayTag Event_AbilitySystem_UnitKilled;
    FGameplayTag Event_Montage;
    FGameplayTag Event_Montage_End;

    FGameplayTag Montage;
    FGameplayTag Montage_Combat;

    FGameplayTag Effect_Info;

    FGameplayTag DamageTag;
    FGameplayTag DamageTag_Blocked;
    FGameplayTag DamageTag_Critical;

    FGameplayTag Alteration_Dead;
    FGameplayTag Alteration_Stunned;
    FGameplayTag Alteration_Rooted;
    FGameplayTag Alteration_Knockback;
    FGameplayTag Alteration_Silenced;
    FGameplayTag Alteration_Disarmed;
    FGameplayTag Alteration_Slowed;

    FGameplayTag Ability_ID;
    FGameplayTag Ability_Cooldown;
    FGameplayTag Ability_Cost;

    FGameplayTag Ability_Status;
    FGameplayTag Ability_Status_Locked;
	FGameplayTag Ability_Status_Eligible;
	FGameplayTag Ability_Status_Unlocked;
	FGameplayTag Ability_Status_Equipped;

    FGameplayTag Ability_Type;
	FGameplayTag Ability_Type_Activable;
	FGameplayTag Ability_Type_Passive;
	FGameplayTag Ability_Type_Utility;

    FGameplayTag Ability_Interruptible_Death;
    FGameplayTag Ability_Interruptible_Stunned;
    FGameplayTag Ability_Interruptible_Rooted;
    FGameplayTag Ability_Interruptible_Knockback;
    FGameplayTag Ability_Interruptible_Silenced;
    FGameplayTag Ability_Interruptible_Disarmed;

    FGameplayTag Magnitude_Damage;
    FGameplayTag Magnitude_Duration;
    FGameplayTag Magnitude_Factor;

    FGameplayTag Player_UI_Disable_Cursor;
    FGameplayTag Player_UI_Enable_Cursor;
    FGameplayTag Player_UI_Disable_AbilityInputs;
    FGameplayTag Player_UI_Disable_CursorTrace;
    FGameplayTag Player_UI_Enable_ForwardCameraLock;
    FGameplayTag Player_UI_Disable_ForwardCameraLock;

protected:

private:
    static FGRGameplayTags GameplayTags;
};
