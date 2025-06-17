// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GRVitalAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GASRPG_API UGRVitalAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

    UGRVitalAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** Vital Attributes */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	ATTRIBUTE_ACCESSORS(UGRVitalAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UGRVitalAttributeSet, MaxHealth);

	/** Meta Attributes */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UGRVitalAttributeSet, IncomingDamage);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, UGRVitalAttributeSet*, AttributeSet, const FGameplayEffectSpec&, KillingEffectSpec);

	UPROPERTY(BlueprintAssignable, Category = "Death")
	FOnDeath OnDeath;

private:

	void ExtractEffectModProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void HandleModificationData_IncomingDamage(const FGameplayEffectModCallbackData& Data);
	void PopFloatingDamages(float Damages, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props);
    void SendGameplayEventToSourceActor(const FGameplayTag& EventTag, float Magnitude, const FGameplayEffectModCallbackData& Data, const FEffectProperties& Props);

};
