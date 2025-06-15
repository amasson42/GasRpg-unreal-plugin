// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/GROverlayController.h"

#include "UI/WidgetController/Components/GRVitalAttributesWcc.h"
#include "UI/WidgetController/Components/GREffectInfoTagWcc.h"
#include "UI/WidgetController/Components/GRAbilitiesInputWcc.h"

void UGROverlayController::Construct()
{
    Super::Construct();

    VitalAttributesWcc = AddComponent<UGRVitalAttributesWcc>("VitalAttributes");
    EffectInfoTagWcc = AddComponent<UGREffectInfoTagWcc>("EffectInfoTag");
    AbilitiesInputWcc = AddComponent<UGRAbilitiesInputWcc>("AbilitiesInput");
}

void UGROverlayController::ObservedActorSet()
{
    Super::ObservedActorSet();

    if (IsValid(VitalAttributesWcc))
        VitalAttributesWcc->Initialize(AbilitySystemComponent, AttributeSet);
    if (IsValid(EffectInfoTagWcc))
        EffectInfoTagWcc->Initialize(AbilitySystemComponent);
    if (IsValid(AbilitiesInputWcc))
        AbilitiesInputWcc->Initialize(AbilitySystemComponent);
}
