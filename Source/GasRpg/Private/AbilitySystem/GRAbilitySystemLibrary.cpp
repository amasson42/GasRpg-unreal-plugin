// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "GameplayEffect.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/GRMainAttributeSet.h"
#include "AbilitySystem/GRMainAttributeList.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GasRpgGameplayTags.h"

//   ____                            _             _____  __  __           _
//  / ___| __ _ _ __ ___   ___ _ __ | | __ _ _   _| ____|/ _|/ _| ___  ___| |_ ___
// | |  _ / _` | '_ ` _ \ / _ \ '_ \| |/ _` | | | |  _| | |_| |_ / _ \/ __| __/ __|
// | |_| | (_| | | | | | |  __/ |_) | | (_| | |_| | |___|  _|  _|  __/ (__| |_\__ \
//  \____|\__,_|_| |_| |_|\___| .__/|_|\__,_|\__, |_____|_| |_|  \___|\___|\__|___/
//                            |_|            |___/

FActiveGameplayEffectHandle UGRAbilitySystemLibrary::ApplyGameplayEffectWithParameters(const FGameplayEffectParameters &EffectParams, UAbilitySystemComponent *SourceASC, UAbilitySystemComponent *TargetASC)
{
    if (!IsValid(EffectParams.Class))
        return FActiveGameplayEffectHandle();

    if (!IsValid(SourceASC))
        SourceASC = TargetASC;

    if (!IsValid(TargetASC))
        return FActiveGameplayEffectHandle();

    FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
    EffectContext.AddSourceObject(SourceASC->GetAvatarActor());

    if (!EffectParams.HitCollision.ImpactPoint.IsZero())
        EffectContext.AddHitResult(EffectParams.HitCollision);

    if (!EffectParams.HitImpulse.IsZero())
        SetHitImpulse(EffectContext, EffectParams.HitImpulse);

    if (IsValid(EffectParams.SourceAbility))
        EffectContext.SetAbility(EffectParams.SourceAbility);

    const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(EffectParams.Class, EffectParams.Level, EffectContext);

    for (const TPair<FGameplayTag, float> &SetByCallerMagnitude : EffectParams.SetByCallerMagnitudes)
    {
        UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, SetByCallerMagnitude.Key, SetByCallerMagnitude.Value);
    }

    return SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetASC);
}

bool UGRAbilitySystemLibrary::CheckGameplayEffectSpecHasTag(const FGameplayEffectSpec &EffectSpec, FGameplayTag Tag)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);
    return TagContainer.HasTag(Tag);
}

void UGRAbilitySystemLibrary::GetContextFromGameplayEffectSpec(const FGameplayEffectSpec &EffectSpec, FGameplayEffectContextHandle &Context)
{
    Context = EffectSpec.GetContext();
}

void UGRAbilitySystemLibrary::ExtractPropertiesFromGameplayEffectContextHandle(const FGameplayEffectContextHandle &Context, FEffectProperties &Props)
{
    Props.EffectContextHandle = Context;
    Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

    if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
        Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
        if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
        {
            if (const APawn *Pawn = Cast<APawn>(Props.SourceAvatarActor))
            {
                Props.SourceController = Pawn->GetController();
            }
        }
        if (Props.SourceController)
        {
            Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
        }
    }
}

bool UGRAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle &EffectContextHandle)
{
    if (const FGRGameplayEffectContext *EffectContext = static_cast<const FGRGameplayEffectContext *>(EffectContextHandle.Get()))
    {
        return EffectContext->bIsBlockedHit;
    }
    return false;
}

void UGRAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle &EffectContextHandle, bool bNewIsBlockedHit)
{
    if (FGRGameplayEffectContext *EffectContext = static_cast<FGRGameplayEffectContext *>(EffectContextHandle.Get()))
    {
        EffectContext->bIsBlockedHit = bNewIsBlockedHit;
    }
}

bool UGRAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle &EffectContextHandle)
{
    if (const FGRGameplayEffectContext *EffectContext = static_cast<const FGRGameplayEffectContext *>(EffectContextHandle.Get()))
    {
        return EffectContext->bIsCriticalHit;
    }
    return false;
}

void UGRAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle &EffectContextHandle, bool bNewIsCriticalHit)
{
    if (FGRGameplayEffectContext *EffectContext = static_cast<FGRGameplayEffectContext *>(EffectContextHandle.Get()))
    {
        EffectContext->bIsCriticalHit = bNewIsCriticalHit;
    }
}

FVector UGRAbilitySystemLibrary::GetHitImpulse(const FGameplayEffectContextHandle &EffectContextHandle)
{
    if (const FGRGameplayEffectContext *EffectContext = static_cast<const FGRGameplayEffectContext *>(EffectContextHandle.Get()))
    {
        return EffectContext->HitImpulse;
    }
    return FVector::ZeroVector;
}

void UGRAbilitySystemLibrary::SetHitImpulse(FGameplayEffectContextHandle &EffectContextHandle, FVector NewHitImpulse)
{
    if (FGRGameplayEffectContext *EffectContext = static_cast<FGRGameplayEffectContext *>(EffectContextHandle.Get()))
    {
        EffectContext->HitImpulse = NewHitImpulse;
    }
}

void UGRAbilitySystemLibrary::GetGameplayEffectModAtLevel(TSubclassOf<UGameplayEffect> EffectClass, float Level, TMap<FString, float> &Attributes)
{
    UGameplayEffect *Effect = EffectClass.GetDefaultObject();

    if (!IsValid(Effect))
        return;

    for (const FGameplayModifierInfo &Modifier : Effect->Modifiers)
    {
        float AttributeMagnitude;
        Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level, AttributeMagnitude);

        FString AttributeName = Modifier.Attribute.GetName();

        if (float *PreviousValue = Attributes.Find(AttributeName))
            Attributes.Add(AttributeName, *PreviousValue + AttributeMagnitude);
        else
            Attributes.Add(AttributeName, AttributeMagnitude);
    }
}

//   ____                            _               _____
//  / ___| __ _ _ __ ___   ___ _ __ | | __ _ _   _  |_   _|_ _  __ _ ___
// | |  _ / _` | '_ ` _ \ / _ \ '_ \| |/ _` | | | |   | |/ _` |/ _` / __|
// | |_| | (_| | | | | | |  __/ |_) | | (_| | |_| |   | | (_| | (_| \__ \
//  \____|\__,_|_| |_| |_|\___| .__/|_|\__,_|\__, |   |_|\__,_|\__, |___/
//                            |_|            |___/             |___/

FGameplayTag UGRAbilitySystemLibrary::GetFirstMatchingTagFromTagContainer(const FGameplayTagContainer &TagContainer, FGameplayTag MatchingTag)
{
    for (FGameplayTag Tag : TagContainer)
    {
        if (Tag.MatchesTag(MatchingTag))
            return Tag;
    }
    return FGameplayTag::EmptyTag;
}

void UGRAbilitySystemLibrary::GetMatchingTagsFromTagContainer(const FGameplayTagContainer &TagContainer, FGameplayTag MatchingTag, FGameplayTagContainer &MatchingTags)
{
    for (FGameplayTag Tag : TagContainer)
    {
        if (Tag.MatchesTag(MatchingTag))
            MatchingTags.AddTag(Tag);
    }
}

bool UGRAbilitySystemLibrary::RemoveMatchingTagsFromTagContainer(FGameplayTagContainer &TagContainer, FGameplayTag MatchingTag)
{
    TArray<FGameplayTag> ToRemoveTags;

    for (FGameplayTag Tag : TagContainer)
    {
        if (Tag.MatchesTag(MatchingTag))
        {
            ToRemoveTags.Add(Tag);
        }
    }
    for (const FGameplayTag &ToRemoveTag : ToRemoveTags)
    {
        TagContainer.RemoveTag(ToRemoveTag);
    }
    return !ToRemoveTags.IsEmpty();
}

//     _   _   _        _ _           _
//    / \ | |_| |_ _ __(_) |__  _   _| |_ ___  ___
//   / _ \| __| __| '__| | '_ \| | | | __/ _ \/ __|
//  / ___ \ |_| |_| |  | | |_) | |_| | ||  __/\__ \
// /_/   \_\__|\__|_|  |_|_.__/ \__,_|\__\___||___/

#define TagDoFunction(AttributeName, CategoryName) \
    Function.ExecuteIfBound(FGRGameplayTags::Get().Attributes_##CategoryName##_##AttributeName);

void UGRAbilitySystemLibrary::ForEachVitalAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Vital(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachVitalNoMaxAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Vital_NoMax(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachPrimaryAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Primary(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachSecondaryAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Secondary(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachMetaAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Meta(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachReplicatedAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Replicated(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachStatsAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_Stats(TagDoFunction);
}

void UGRAbilitySystemLibrary::ForEachAttributes(FGameplayTagDelegate Function)
{
    FOREACH_ATTRIBUTE_All(TagDoFunction);
}

//     _    _     _ _ _ _   _
//    / \  | |__ (_) (_) |_(_) ___  ___
//   / _ \ | '_ \| | | | __| |/ _ \/ __|
//  / ___ \| |_) | | | | |_| |  __/\__ \
// /_/   \_\_.__/|_|_|_|\__|_|\___||___/

FGameplayTag UGRAbilitySystemLibrary::GetAbilityIdFromAbilityClass(TSubclassOf<UGameplayAbility> AbilityClass)
{
    return UGRAbilitySystemComponent::GetAbilityIDTagFromAbility(AbilityClass.GetDefaultObject());
}

FGameplayTag UGRAbilitySystemLibrary::GetTypeTagFromAbilityClass(TSubclassOf<UGameplayAbility> AbilityClass)
{
    return UGRAbilitySystemComponent::GetTypeTagFromAbility(AbilityClass.GetDefaultObject());
}

FGameplayTag UGRAbilitySystemLibrary::GetCooldownTagFromAbilityClass(TSubclassOf<UGameplayAbility> AbilityClass)
{
    return UGRAbilitySystemComponent::GetCooldownTagFromAbility(AbilityClass.GetDefaultObject());
}

void UGRAbilitySystemLibrary::GetAbilityCostAtLevel(TSubclassOf<UGameplayAbility> AbilityClass, float Level, TMap<FString, float> &Costs)
{
    if (IsValid(AbilityClass))
    {
        UGameplayAbility *DefaultObject = AbilityClass.GetDefaultObject();
        if (!IsValid(DefaultObject))
            return;

        UGameplayEffect *CostEffect = DefaultObject->GetCostGameplayEffect();
        if (!IsValid(CostEffect))
            return;

        for (const FGameplayModifierInfo &Modifier : CostEffect->Modifiers)
        {
            float CostMagnitude;
            Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level, CostMagnitude);
            CostMagnitude *= -1;

            FString CostName = Modifier.Attribute.GetName();

            if (float *PreviousValue = Costs.Find(CostName))
                Costs.Add(CostName, *PreviousValue + CostMagnitude);
            else
                Costs.Add(CostName, CostMagnitude);
        }
    }
}

float UGRAbilitySystemLibrary::GetAbilityCooldownTimeAtLevel(TSubclassOf<UGameplayAbility> AbilityClass, float Level)
{
    if (IsValid(AbilityClass))
    {
        UGameplayAbility *DefaultObject = AbilityClass.GetDefaultObject();
        if (!IsValid(DefaultObject))
            return 0.0f;

        UGameplayEffect *CooldownEffect = DefaultObject->GetCooldownGameplayEffect();
        if (!IsValid(CooldownEffect))
            return 0.0f;

        float CooldownMagnitude;
        CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(Level, CooldownMagnitude);
        return CooldownMagnitude;
    }
    return 0.0f;
}

//   ____                           _
//  / ___| ___ _ __   ___ _ __ __ _| |
// | |  _ / _ \ '_ \ / _ \ '__/ _` | |
// | |_| |  __/ | | |  __/ | | (_| | |
//  \____|\___|_| |_|\___|_|  \__,_|_|

void UGRAbilitySystemLibrary::MakeTargetDataHandleWithSingleHitResult(const FHitResult &HitResult, FGameplayAbilityTargetDataHandle &Handle)
{
    FGameplayAbilityTargetData_SingleTargetHit *Data = new FGameplayAbilityTargetData_SingleTargetHit();
    Data->HitResult = HitResult;
    Handle.Add(Data);
}

void UGRAbilitySystemLibrary::MakeTargetDataHandleWithSingleVector(const FVector &Vector, FGameplayAbilityTargetDataHandle &Handle)
{
    FGameplayAbilityTargetData_Vector *Data = new FGameplayAbilityTargetData_Vector();
    Data->Vector = Vector;
    Handle.Add(Data);
}

void UGRAbilitySystemLibrary::GetVectorFromTargetData(const FGameplayAbilityTargetDataHandle &Handle, const int Index, FVector &Vector)
{
    const FGameplayAbilityTargetData *Data = Handle.Get(Index);

    if (Data == nullptr)
    {
        return;
    }

    if (Data->GetScriptStruct() == FGameplayAbilityTargetData_Vector::StaticStruct())
    {
        // Here is when you would do the cast because we know its the correct type already
        const FGameplayAbilityTargetData_Vector *VectorData = static_cast<const FGameplayAbilityTargetData_Vector *>(Data);
        Vector = VectorData->Vector;
    }
}
