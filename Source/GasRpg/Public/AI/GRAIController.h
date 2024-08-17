// Copyright Amasson

#pragma once

#include "CoreMinimal.h"
#include "FactionSystem/FactionAIController.h"
#include "GRAIController.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API AGRAIController : public AFactionAIController
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
    TObjectPtr<class UBehaviorTree> BehaviorTree;

};
