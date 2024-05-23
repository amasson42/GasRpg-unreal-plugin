// Copyright Amasson


#include "Component/GasRpgCharacterBaseComponent.h"
#include "Character/GRCharacterBase.h"

UGasRpgCharacterBaseComponent::UGasRpgCharacterBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    SetIsReplicatedByDefault(true);
}

void UGasRpgCharacterBaseComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UGasRpgCharacterBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AGRCharacterBase* UGasRpgCharacterBaseComponent::GetGasRpgCharacter() const
{
    return Cast<AGRCharacterBase>(GetOwner());
}

void UGasRpgCharacterBaseComponent::AbilitySystemComponentInitialized_Implementation(UAbilitySystemComponent* ASC)
{
    
}
