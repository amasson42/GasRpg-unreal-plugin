
#include "GasRpgGameplayTags.h"
#include "GameplayTagsManager.h"

FGRGameplayTags FGRGameplayTags::GameplayTags;


void FGRGameplayTags::InitializeNativeGameplayTags()
{
    UGameplayTagsManager& Manager(UGameplayTagsManager::Get());

    /** Attributes */

#define INITIALIZE_ATTRIBUTE_TAG(AttributeName, CategoryName) \
    GameplayTags.Attributes_##CategoryName##_##AttributeName = Manager.AddNativeGameplayTag( \
        FName(FString::Printf(TEXT("Attributes.%s.%s"), TEXT(#CategoryName), TEXT(#AttributeName))), \
        FString("Attribute identifier tag") \
    );

    FOREACH_ATTRIBUTE_All(INITIALIZE_ATTRIBUTE_TAG);

    /** InputTag */

    GameplayTags.InputTag = Manager.AddNativeGameplayTag(
        FName("InputTag"),
        FString("Root tag ability inputs")
    );


    /** Event */

    GameplayTags.Event = Manager.AddNativeGameplayTag(
        FName("Event"),
        FString("Root tag for event to send to an actor")
    );

    GameplayTags.Event_AbilitySystem_DamageApplied = Manager.AddNativeGameplayTag(
        FName("Event.AbilitySystem.DamageApplied"),
        FString("Event triggered when the actor has applied damages")
    );

    GameplayTags.Event_AbilitySystem_UnitKilled = Manager.AddNativeGameplayTag(
        FName("Event.AbilitySystem.UnitKill"),
        FString("Event triggered when the actor has killed something")
    );

    GameplayTags.Event_Montage = Manager.AddNativeGameplayTag(
        FName("Event.Montage"),
        FString("Root tag for montages events")
    );

    GameplayTags.Event_Montage_End = Manager.AddNativeGameplayTag(
        FName("Event.Montage.End"),
        FString("Event triggered when a montage is no longer relevant")
    );

    GameplayTags.Effect_Info = Manager.AddNativeGameplayTag(
        FName("Effect.Info"),
        FString("Root tag for effects that get displayed on screen")
    );

    GameplayTags.DamageTag = Manager.AddNativeGameplayTag(
        FName("DamageTag"),
        FString("Tags to send to the floating damage widget")
    );

    GameplayTags.DamageTag_Blocked = Manager.AddNativeGameplayTag(
        FName("DamageTag.Blocked"),
        FString("The damage was blocked blocked")
    );

    GameplayTags.DamageTag_Critical = Manager.AddNativeGameplayTag(
        FName("DamageTag.Critical"),
        FString("The damage was a critical strike")
    );


    /* Alteration */

    GameplayTags.Alteration_Dead = Manager.AddNativeGameplayTag(
        FName("Alteration.Dead"),
        FString("The character is dead")
    );

    GameplayTags.Alteration_Stunned = Manager.AddNativeGameplayTag(
        FName("Alteration.Stunned"),
        FString("The character is stunned and cannot act")
    );

    GameplayTags.Alteration_Rooted = Manager.AddNativeGameplayTag(
        FName("Alteration.Rooted"),
        FString("The character is rooted and cannot move")
    );

    GameplayTags.Alteration_Knockback = Manager.AddNativeGameplayTag(
        FName("Alteration.Knockback"),
        FString("The character is being knocked back")
    );

    GameplayTags.Alteration_Silenced = Manager.AddNativeGameplayTag(
        FName("Alteration.Silenced"),
        FString("The character is silenced and cannot cast spells")
    );

    GameplayTags.Alteration_Disarmed = Manager.AddNativeGameplayTag(
        FName("Alteration.Disarmed"),
        FString("The character is disarmed and cannot attack")
    );

    GameplayTags.Alteration_Slowed = Manager.AddNativeGameplayTag(
        FName("Alteration.Slowed"),
        FString("The character is slowed")
    );


    /* Ability */

    GameplayTags.Ability_ID = Manager.AddNativeGameplayTag(
        FName("Ability.ID"),
        FString("Root ability identifier tag")
    );

    GameplayTags.Ability_Cooldown = Manager.AddNativeGameplayTag(
        FName("Ability.Cooldown"),
        FString("Root ability cooldown tag")
    );

    GameplayTags.Ability_Cost = Manager.AddNativeGameplayTag(
        FName("Ability.Cost"),
        FString("Root ability cost tag")
    );


    /* Ability Status */

    GameplayTags.Ability_Status = Manager.AddNativeGameplayTag(
        FName("Ability.Status"),
        FString("Root ability status")
    );

    GameplayTags.Ability_Status_Locked = Manager.AddNativeGameplayTag(
        FName("Ability.Status.Locked"),
        FString("Ability not available yet")
    );

	GameplayTags.Ability_Status_Eligible = Manager.AddNativeGameplayTag(
        FName("Ability.Status.Eligible"),
        FString("Ability can be learn")
    );

	GameplayTags.Ability_Status_Unlocked = Manager.AddNativeGameplayTag(
        FName("Ability.Status.Unlocked"),
        FString("Ability can be put in action bar")
    );

	GameplayTags.Ability_Status_Equipped = Manager.AddNativeGameplayTag(
        FName("Ability.Status.Equipped"),
        FString("Ability is set in action bar")
    );


    /* Ability Types */

	GameplayTags.Ability_Type = Manager.AddNativeGameplayTag(
        FName("Ability.Type"),
        FString("Root ability type")
    );

	GameplayTags.Ability_Type_Activable = Manager.AddNativeGameplayTag(
        FName("Ability.Type.Activable"),
        FString("Ability must be equipped and activated")
    );

	GameplayTags.Ability_Type_Passive = Manager.AddNativeGameplayTag(
        FName("Ability.Type.Passive"),
        FString("Ability is permanently activated when equipped")
    );

	GameplayTags.Ability_Type_Utility = Manager.AddNativeGameplayTag(
        FName("Ability.Type.Utility"),
        FString("Ability permanently available as part of the game mechanics")
    );

    GameplayTags.Ability_Interruptible_Death = Manager.AddNativeGameplayTag(
        FName("Ability.Interruptible.Death"),
        FString("Ability is interrupted by death")
    );

    GameplayTags.Ability_Interruptible_Stunned = Manager.AddNativeGameplayTag(
        FName("Ability.Interruptible.Stunned"),
        FString("Ability is interrupted on stun")
    );

    GameplayTags.Ability_Interruptible_Rooted = Manager.AddNativeGameplayTag(
        FName("Ability.Interruptible.Rooted"),
        FString("Ability is interrupted when rooted")
    );

    GameplayTags.Ability_Interruptible_Knockback = Manager.AddNativeGameplayTag(
        FName("Ability.Interruptible.Knockback"),
        FString("Ability can be interrupted by knockback")
    );

    GameplayTags.Ability_Interruptible_Silenced = Manager.AddNativeGameplayTag(
        FName("Ability.Interruptible.Silenced"),
        FString("Ability is interrupted when silenced")
    );

    GameplayTags.Ability_Interruptible_Disarmed = Manager.AddNativeGameplayTag(
        FName("Ability.Interruptible.Disarmed"),
        FString("Ability is interrupted when disarmed")
    );


    /** Magnitude */

    GameplayTags.Magnitude_Damage = Manager.AddNativeGameplayTag(
        FName("Magnitude.Damage"),
        FString("Effect general purpose damage magnitude")
    );

    GameplayTags.Magnitude_Duration = Manager.AddNativeGameplayTag(
        FName("Magnitude.Duration"),
        FString("Effect duration magnitude")
    );

    GameplayTags.Magnitude_Factor = Manager.AddNativeGameplayTag(
        FName("Magnitude.Factor"),
        FString("Effect general purpose factor magnitude")
    );


    /** Player event */

    GameplayTags.Player_Hide_Cursor = Manager.AddNativeGameplayTag(
        FName("Player.Hide.Cursor"),
        FString("Hide player cursor")
    );

    GameplayTags.Player_Show_Cursor = Manager.AddNativeGameplayTag(
        FName("Player.Show.Cursor"),
        FString("Show player cursor")
    );

    GameplayTags.Player_Block_AbilityInputs = Manager.AddNativeGameplayTag(
        FName("Player.Block.AbilityInputs"),
        FString("Prevent player from using abilities with inputs")
    );

    GameplayTags.Player_Block_CursorTrace = Manager.AddNativeGameplayTag(
        FName("Player.Block.CursorTrace"),
        FString("Prevent player from cursor tracing in different interaction systems")
    );

    GameplayTags.Player_Lock_Forward = Manager.AddNativeGameplayTag(
        FName("Player.Lock.Forward"),
        FString("Lock player camera looking forward")
    );

    GameplayTags.Player_Unlock_Forward = Manager.AddNativeGameplayTag(
        FName("Player.Unlock.Forward"),
        FString("Unlock player camera looking forward")
    );

}
