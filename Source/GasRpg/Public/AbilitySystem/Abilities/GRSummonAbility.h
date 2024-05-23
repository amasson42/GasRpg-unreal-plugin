// Amasson

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GRGameplayAbility.h"
#include "GRSummonAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GASRPG_API UGRSummonAbility : public UGRGameplayAbility
{
	GENERATED_BODY()
	
public:

	UGRSummonAbility();

	UFUNCTION(BlueprintCallable, Category = "Summon")
	AActor* SummonActor(TSubclassOf<AActor> Class, const FVector& Location, float YawOffset = 0);

	UFUNCTION()
	void SummonDestroyed(AActor* DestroyedActor);

	/* Spawn Locations */

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnArcLocations();

	UPROPERTY(EditDefaultsOnly, Category = "SummonLocation")
	int32 SpawnCount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "SummonLocation")
	float SpawnMinDistance = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "SummonLocation")
	float SpawnMaxDistance = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "SummonLocation")
	float SpawnSpreadAngle = 80.0f;

	UPROPERTY(EditDefaultsOnly, Category = "SummonLocation")
    bool bProjectToNavigation = true;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpawnedActorSignature, UGRSummonAbility*, SummonAbility, AActor*, SpawnedActor);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorDestroyedSignature, UGRSummonAbility*, SummonAbility, AActor*, DestroyedActor);

	/* Spawned Actors */

	UPROPERTY(BlueprintReadOnly, Category = "State")
	TArray<TObjectPtr<AActor>> SpawnedActors;

	UPROPERTY(BlueprintAssignable)
	FSpawnedActorSignature OnSpawnedActor;
	UPROPERTY(BlueprintAssignable)
	FActorDestroyedSignature OnActorDestroyed;

};
