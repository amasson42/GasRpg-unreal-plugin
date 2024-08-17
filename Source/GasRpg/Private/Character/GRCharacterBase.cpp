// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRCharacterBase.h"
#include "Player/GRPlayerController.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "AbilitySystem/Effect/GRPrimaryAttributesBaseEffect.h"
#include "AbilitySystem/Effect/GRSecondaryAttributesBaseEffect.h"
#include "AbilitySystem/GRAbilitySystemLibrary.h"
#include "AbilitySystem/GRMainAttributeSet.h"
#include "Data/GRCharacterKit.h"
#include "FactionSystem/FactionData.h"


AGRCharacterBase::AGRCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AGRCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGRCharacterBase::RegisterGameplayTagEvent(FGameplayTag EventTag, EGameplayTagEventType::Type TagEventType, FTagCountChangeSignature OnTagCountChanged)
{
	if (!IsValid(AbilitySystemComponent))
        return;

    AbilitySystemComponent->RegisterGameplayTagEvent(EventTag, TagEventType)
        .AddLambda([OnTagCountChanged](const FGameplayTag& CallbackTag, int32 NewCount) {
            OnTagCountChanged.ExecuteIfBound(CallbackTag, NewCount);
        });
}

void AGRCharacterBase::RegisterAttributeEvent(FGameplayAttribute Attribute, FAttributeValueChangeSignature OnAttributeValueChanged)
{
    if (!IsValid(AbilitySystemComponent))
        return;
    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute)
        .AddLambda([OnAttributeValueChanged](const FOnAttributeChangeData& Data) {
            OnAttributeValueChanged.ExecuteIfBound(Data.OldValue, Data.NewValue);
        });
}

void AGRCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(CharacterKit, TEXT("CharacterKit not set for %s"), *GetNameSafe(this));
}


/** RpgCharacter Interface */

int32 AGRCharacterBase::GetCharacterLevel_Implementation() const
{
    return 1;
}

FVector AGRCharacterBase::GetSocketLocation_Implementation(FGameplayTag SocketTagName) const
{
    return GetActorLocation();
}

USceneComponent* AGRCharacterBase::GetSocketComponent_Implementation(FGameplayTag SocketTag) const
{
    return GetRootComponent();
}

FRpgCharacterMontage AGRCharacterBase::GetMontage_Implementation(FGameplayTag MontageTag) const
{
    const FRpgCharacterMontageArray *MontageArray = RpgMontages.Find(MontageTag);
    if (!MontageArray || MontageArray->Montages.IsEmpty())
        return FRpgCharacterMontage();

    return MontageArray->Montages[FMath::RandRange(0, MontageArray->Montages.Num() - 1)];
}

void AGRCharacterBase::ActivateRpgEventForTag_Implementation(FGameplayTag RpgEventTag, UObject* Activator)
{
    FObjectSet* Set = RpgEventActivators.Find(RpgEventTag);
    if (Set)
    {
        Set->Objects.Add(Activator);
    }
    else
    {
        FObjectSet NewSet;
        NewSet.Objects.Add(Activator);
        RpgEventActivators.Add(RpgEventTag, NewSet);
        ToggleRpgEventForTag(RpgEventTag, true);
    }
}

void AGRCharacterBase::DeactivateRpgEventForTag_Implementation(FGameplayTag RpgEventTag, UObject* Activator)
{
    FObjectSet* Set = RpgEventActivators.Find(RpgEventTag);
    if (Set)
    {
        Set->Objects.Remove(Activator);
        if (Set->Objects.IsEmpty())
        {
            RpgEventActivators.Remove(RpgEventTag);
            ToggleRpgEventForTag(RpgEventTag, false);
        }
    }
}


bool AGRCharacterBase::IsDead_Implementation() const
{
    if (!IsValid(AttributeSet))
		return false;

	if (UGRMainAttributeSet* AS = Cast<UGRMainAttributeSet>(AttributeSet))
	{
		return AS->GetHealth() <= 0.0f;
	}

	return false;
}

IRpgCharacterInterface::FOnASCRegisteredDelegate& AGRCharacterBase::GetOnASCRegisteredDelegate()
{
    return OnASCRegistered;
}

FOnDeathBroadcastSignature& AGRCharacterBase::GetOnDeathDelegate()
{
    return OnDeath;
}

/** Ability System */

void AGRCharacterBase::InitAbilitySystem()
{
	if (UGRAbilitySystemComponent* ASC = Cast<UGRAbilitySystemComponent>(AbilitySystemComponent))
    {
        ASC->AbilitySystemInitDone();
    }
	AbilitySystemInitialized(AbilitySystemComponent);
	OnASCRegistered.Broadcast(AbilitySystemComponent);

	AddCharacterBaseEffects();
	AddCharacterAbilities();
	ApplyBeginEffects();
}

void AGRCharacterBase::AbilitySystemInitialized_Implementation(UAbilitySystemComponent* ASC)
{
	
}


void AGRCharacterBase::AddCharacterBaseEffects()
{
    if (!HasAuthority())
        return;

    if (!IsValid(AbilitySystemComponent))
        return;

    const float CharacterLevel = static_cast<float>(IRpgCharacterInterface::Execute_GetCharacterLevel(this));

	UGRAbilitySystemComponent* ASC = Cast<UGRAbilitySystemComponent>(AbilitySystemComponent);

	if (!IsValid(ASC))
        return

    ASC->SetBaseEffectsLevel(CharacterLevel);

    TArray<TSubclassOf<UGameplayEffect>> BaseEffects;
    CharacterKit->GetBaseEffects(BaseEffects);

	for(const TSubclassOf<UGameplayEffect>& EffectClass : BaseEffects)
    {
        ASC->AddBaseEffect(EffectClass);
    }
}

void AGRCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())
        return;

	UGRAbilitySystemComponent* ASC = Cast<UGRAbilitySystemComponent>(GetAbilitySystemComponent());
    if (!IsValid(ASC))
        return;

    TArray<FGameplayAbilityGrant> StartupAbilities;
    CharacterKit->GetStartupAbilities(StartupAbilities);
    ASC->GrantStartupAbilities(StartupAbilities);
}

void AGRCharacterBase::ApplyBeginEffects()
{
	if (!HasAuthority())
        return;

    if (!IsValid(AbilitySystemComponent))
        return;

    TArray<FGameplayEffectParameters> BeginEffects;
    CharacterKit->GetOnBeginEffects(BeginEffects);
	for(const FGameplayEffectParameters& Effect : BeginEffects)
    {
		UGRAbilitySystemLibrary::ApplyGameplayEffectWithParameters(Effect, nullptr, AbilitySystemComponent);
    }
}
