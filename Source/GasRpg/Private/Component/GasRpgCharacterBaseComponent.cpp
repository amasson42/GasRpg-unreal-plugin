// Copyright Amasson


#include "Component/GasRpgCharacterBaseComponent.h"
#include "Pawn/GasPawnInterface.h"

UGasRpgCharacterBaseComponent::UGasRpgCharacterBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    SetIsReplicatedByDefault(true);
}

void UGasRpgCharacterBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	TScriptInterface<IGasPawnInterface> RpgPawn = GetGasRpgPawn();
	if (RpgPawn)
	{
		FWithInitializedAbilitySystemDelegate Delegate;
		Delegate.BindDynamic(this, &ThisClass::AbilitySystemComponentInitialized);
		RpgPawn->WithInitializedAbilitySystem(Delegate);
	}
}

void UGasRpgCharacterBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

TScriptInterface<IGasPawnInterface> UGasRpgCharacterBaseComponent::GetGasRpgPawn() const
{
	if (GetOwner() && GetOwner()->GetClass()->ImplementsInterface(UGasPawnInterface::StaticClass()))
	    return GetOwner();
	return nullptr;
}

void UGasRpgCharacterBaseComponent::AbilitySystemComponentInitialized_Implementation(UAbilitySystemComponent* ASC)
{
    
}
