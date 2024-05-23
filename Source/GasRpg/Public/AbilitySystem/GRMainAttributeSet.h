// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "GRMainAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GASRPG_API UGRMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

    UGRMainAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    /* [MainAttributeListBoilerplate] All attributes */

	/** Vital Attributes */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, MaxStamina);

	/** Primary Attributes */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	UFUNCTION() void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Valor, Category = "Primary Attributes")
	FGameplayAttributeData Valor;
	UFUNCTION() void OnRep_Valor(const FGameplayAttributeData& OldValor) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Valor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Wisdom, Category = "Primary Attributes")
	FGameplayAttributeData Wisdom;
	UFUNCTION() void OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Wisdom);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Divinity, Category = "Primary Attributes")
	FGameplayAttributeData Divinity;
	UFUNCTION() void OnRep_Divinity(const FGameplayAttributeData& OldDivinity) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, Divinity);

	/** Secondary Attributes */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDefense, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalDefense;
	UFUNCTION() void OnRep_PhysicalDefense(const FGameplayAttributeData& OldPhysicalDefense) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, PhysicalDefense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellDefense, Category = "Secondary Attributes")
	FGameplayAttributeData SpellDefense;
	UFUNCTION() void OnRep_SpellDefense(const FGameplayAttributeData& OldSpellDefense) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, SpellDefense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	UFUNCTION() void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, MovementSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MeleeAttack, Category = "Secondary Attributes")
	FGameplayAttributeData MeleeAttack;
	UFUNCTION() void OnRep_MeleeAttack(const FGameplayAttributeData& OldMeleeAttack) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, MeleeAttack);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RangedAttack, Category = "Secondary Attributes")
	FGameplayAttributeData RangedAttack;
	UFUNCTION() void OnRep_RangedAttack(const FGameplayAttributeData& OldRangedAttack) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, RangedAttack);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellAttack, Category = "Secondary Attributes")
	FGameplayAttributeData SpellAttack;
	UFUNCTION() void OnRep_SpellAttack(const FGameplayAttributeData& OldSpellAttack) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, SpellAttack);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockBonus, Category = "Secondary Attributes")
	FGameplayAttributeData BlockBonus;
	UFUNCTION() void OnRep_BlockBonus(const FGameplayAttributeData& OldBlockBonus) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, BlockBonus);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	UFUNCTION() void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	UFUNCTION() void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData StaminaRegeneration;
	UFUNCTION() void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, StaminaRegeneration);

	/** Meta Attributes */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UGRMainAttributeSet, IncomingDamage);


private:

	void ExtractEffectModProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void HandleModificationData_IncomingDamage(const FGameplayEffectModCallbackData& Data);
	void PopFloatingDamages(float Damages, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props);
    void SendGameplayEventToSourceActor(const FGameplayTag& EventTag, float Magnitude, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props);

};
