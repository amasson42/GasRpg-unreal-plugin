// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GASRPG_API UGRGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

    /** Some objects to keep between levels */
    UPROPERTY(BlueprintReadWrite, Category = "Level Payload")
    TMap<FName, TObjectPtr<UObject>> CrossLevelPayloads;

    /** Add a payload object by using the game instance as outer of the object */
	UFUNCTION(BlueprintCallable, Category = "Level Payload", meta = (DeterminesOutputType = "PayloadClass"))
	UObject* AddCrossLevelPayloadFromClass(TSubclassOf<UObject> PayloadClass, FName Key);

	UFUNCTION(BlueprintCallable, Category = "Level Payload")
	void RemoveCrossLevelPayloadWithkey(FName Key);

    /** Get a payload object with a key as the correct class */
	UFUNCTION(BlueprintCallable, Category = "Level Payload", meta = (DeterminesOutputType = "PayloadClass"))
	UObject* GetCrossLevelPayload(FName Key, TSubclassOf<UObject> PayloadClass) const;

};
