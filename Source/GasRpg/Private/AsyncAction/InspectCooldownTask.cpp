// Copyright Amasson


#include "AsyncAction/InspectCooldownTask.h"
#include "AbilitySystemComponent.h"

UInspectCooldownTask* UInspectCooldownTask::InspectCooldown(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InCooldownTag)
{
    UInspectCooldownTask *NewTask = NewObject<UInspectCooldownTask>();
    NewTask->ASC = AbilitySystemComponent;
    NewTask->CooldownTag = InCooldownTag;

    if (!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
    {
        NewTask->EndTask();
        return nullptr;
    }

    AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved)
        .AddUObject(NewTask, &UInspectCooldownTask::CooldownTagChanged);

    AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf
        .AddUObject(NewTask, &UInspectCooldownTask::OnActiveEffectAdded);

    return NewTask;
}

void UInspectCooldownTask::EndTask()
{
    if (!IsValid(ASC)) return;

    ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved)
        .RemoveAll(this);

    SetReadyToDestroy();
    MarkAsGarbage();
}

void UInspectCooldownTask::CooldownTagChanged(const FGameplayTag ChangedTag, int32 NewCount)
{
    if (NewCount == 0)
    {
        CooldownEnd.Broadcast(0.0f, 1.0f);
    }
}

void UInspectCooldownTask::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	if (EffectHasCooldownTag(SpecApplied))
	{
		BroadcastEffectCooldownTime();
	}
}

bool UInspectCooldownTask::EffectHasCooldownTag(const FGameplayEffectSpec& EffectSpec)
{
	FGameplayTagContainer GrantedTags;
	EffectSpec.GetAllGrantedTags(GrantedTags);

    if (GrantedTags.HasTagExact(CooldownTag))
        return true;

    FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);

    if (AssetTags.HasTagExact(CooldownTag))
        return true;

    return false;
}

void UInspectCooldownTask::BroadcastEffectCooldownTime()
{
    FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
    TArray<TPair<float,float>> TimesRemaining = ASC->GetActiveEffectsTimeRemainingAndDuration(GameplayEffectQuery);

    if (TimesRemaining.Num() > 0)
    {
        TPair<float, float> MaxTimeRemaining(0, 0);
        for (TPair<float, float> TimeRemaining : TimesRemaining)
        {
            if (TimeRemaining.Key > MaxTimeRemaining.Key)
            {
                MaxTimeRemaining = TimeRemaining;
            }
        }

        CooldownStart.Broadcast(MaxTimeRemaining.Key, MaxTimeRemaining.Value);
    }
}