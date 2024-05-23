// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile/GRPrimitiveProjectile.h"
#include "GRSphereProjectile.generated.h"

UCLASS()
class GASRPG_API AGRSphereProjectile : public AGRPrimitiveProjectile
{
	GENERATED_BODY()
	
public:

	AGRSphereProjectile();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TObjectPtr<class USphereComponent> Sphere;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

    UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);

};
