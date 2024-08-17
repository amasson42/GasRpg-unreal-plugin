// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Character/RpgCharacterInterface.h"
#include "GameplayTags.h"
#include "GameplayEffectTypes.h"
#include "LibAmassonTypes.h"
#include "GenericTeamAgentInterface.h"
#include "GRCharacterBase.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;
class UGRCharacterKit;

/**
 * GRCharacterBase is the base character class for every character.
 * It's a direct subclass to the engine Character and add multiple
 * utilities to the base class
 * 
 * @see ACharacter
 */ 
UCLASS(Abstract)
class GASRPG_API AGRCharacterBase : public ACharacter, public IAbilitySystemInterface, public IRpgCharacterInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

	AGRCharacterBase();

	IRpgCharacterInterface::FOnASCRegisteredDelegate OnASCRegistered;

	UPROPERTY(BlueprintAssignable)
	FOnDeathBroadcastSignature OnDeath;

	/** Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE const UGRCharacterKit* GetCharacterKit() const { return CharacterKit; }

    DECLARE_DYNAMIC_DELEGATE_TwoParams(FTagCountChangeSignature, FGameplayTag, Tag, int32, NewCount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Event Tag")
	void RegisterGameplayTagEvent(FGameplayTag EventTag, EGameplayTagEventType::Type TagEventType, FTagCountChangeSignature OnTagCountChanged);

    DECLARE_DYNAMIC_DELEGATE_TwoParams(FAttributeValueChangeSignature, float, OldValue, float, NewValue);

    UFUNCTION(BlueprintCallable, Category = "Gameplay Effect|Event Tag")
	void RegisterAttributeEvent(FGameplayAttribute Attribute, FAttributeValueChangeSignature OnAttributeValueChanged);


    /** Faction System */

    virtual FGenericTeamId GetGenericTeamId() const override;

protected:

	virtual void BeginPlay() override;

	/** RpgCharacter Interface*/

	virtual int32 GetCharacterLevel_Implementation() const override;
	virtual FVector GetSocketLocation_Implementation(FGameplayTag SocketTagName) const override;
    virtual USceneComponent* GetSocketComponent_Implementation(FGameplayTag SocketTag) const override;
    virtual FRpgCharacterMontage GetMontage_Implementation(FGameplayTag MontageTag) const override;
    virtual void ActivateRpgEventForTag_Implementation(FGameplayTag RpgEventTag, UObject* Activator) override;
    virtual void DeactivateRpgEventForTag_Implementation(FGameplayTag RpgEventTag, UObject* Activator) override;
	virtual bool IsDead_Implementation() const override;
	virtual IRpgCharacterInterface::FOnASCRegisteredDelegate& GetOnASCRegisteredDelegate() override;
	virtual FOnDeathBroadcastSignature& GetOnDeathDelegate() override;

    UFUNCTION(BlueprintImplementableEvent, Category = "RpgCharacter|Event")
    void ToggleRpgEventForTag(const FGameplayTag& RpgEventTag, bool bNewActive);

    UPROPERTY(EditDefaultsOnly, Category = "RpgCharacter|Montage")
    TMap<FGameplayTag, FRpgCharacterMontageArray> RpgMontages;

    UPROPERTY()
    TMap<FGameplayTag, FObjectSet> RpgEventActivators;

    /** Ability System */

	UFUNCTION()
	virtual void InitAbilitySystem();

	UFUNCTION(BlueprintNativeEvent, Category = "Ability System")
	void AbilitySystemInitialized(UAbilitySystemComponent* ASC);

	void AddCharacterBaseEffects();
	void AddCharacterAbilities();
	void ApplyBeginEffects();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Kit")
	TObjectPtr<UGRCharacterKit> CharacterKit;


    /** Faction System */

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Faction", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UFactionData> Faction;

};
