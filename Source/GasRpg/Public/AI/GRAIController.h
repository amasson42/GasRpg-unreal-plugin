// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GRAIController.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API AGRAIController : public AAIController
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
    TObjectPtr<class UBehaviorTree> BehaviorTree;

};
