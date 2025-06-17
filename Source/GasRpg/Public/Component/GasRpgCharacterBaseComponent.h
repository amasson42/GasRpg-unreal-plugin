// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GasRpgCharacterBaseComponent.generated.h"


/** Component that should be subclassed and added to all blueprints of AGRCharacterBase.
 *  It contains shared blueprint functionnalitites between Player and Npc characters.
*/
UCLASS(BlueprintType, Blueprintable)
class GASRPG_API UGasRpgCharacterBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGasRpgCharacterBaseComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Character Base")
    TScriptInterface<class IGasPawnInterface> GetGasRpgPawn() const;


protected:

	virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Base")
    void AbilitySystemComponentInitialized(UAbilitySystemComponent* ASC);

    friend class AGRCharacterBase;
};
