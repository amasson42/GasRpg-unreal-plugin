// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/GREffectActor.h"
#include "AbilitySystem/GRAbilitySystemTypes.h"
#include "GRPrimitiveProjectile.generated.h"

class UPrimitiveComponent;
class UProjectileMovementComponent;
class UArrowComponent;
class UAbilitySystemComponent;

UCLASS()
class GASRPG_API AGRPrimitiveProjectile : public AGREffectActor
{
	GENERATED_BODY()

public:

	AGRPrimitiveProjectile();

	UPROPERTY(BlueprintReadWrite, Category = "Projectile|Instigator", meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))
	TObjectPtr<class UGameplayAbility> InstigatorAbility;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileCollisionSignature, AGRPrimitiveProjectile*, Projectile, FHitResult, HitResult);

	UPROPERTY(BlueprintAssignable, Category = "Projectile|Collision")
	FProjectileCollisionSignature OnImpact;

    UPROPERTY(BlueprintAssignable, Category = "Projectile|Collision")
    FProjectileCollisionSignature OnOverlap;

    UPROPERTY(BlueprintAssignable, Category = "Projectile|Collision")
    FProjectileCollisionSignature OnHit;

    UPROPERTY(BlueprintAssignable, Category = "Projectile|Collision")
    FProjectileCollisionSignature OnAnyCollision;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Projectile|Collision")
	bool ShouldImpact(const FHitResult& HitResult);

    /** Triggered when an overlap collision occured with an actor and ShouldImpact returned true */
	UFUNCTION(BlueprintNativeEvent, Category = "Projectile|Collision")
	void DidImpact(const FHitResult& HitResult);

    /** Triggered when an overlap collision occured with an actor and ShouldImpact returned false */
	UFUNCTION(BlueprintNativeEvent, Category = "Projectile|Collision")
	void DidOverlap(const FHitResult& HitResult);

    /** Triggered when a hit collision occured with an actor */
    UFUNCTION(BlueprintNativeEvent, Category = "Projectile|Collision")
	void DidHit(const FHitResult& HitResult);

    /** Triggered when a collision occured with an actor */
    UFUNCTION(BlueprintNativeEvent, Category = "Projectile|Collision")
	void DidAnyCollision(const FHitResult& HitResult);

	UFUNCTION()
	void OnPrimitiveOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

    UFUNCTION()
	void OnPrimitiveHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Projectile");
	TObjectPtr<UArrowComponent> ArrowComponent;

};

UINTERFACE(MinimalAPI)
class UProjectileReactionInterface : public UInterface
{
	GENERATED_BODY()
};

class GASRPG_API IProjectileReactionInterface
{
	GENERATED_BODY()

public:

    /** Executed when a projectile begin overlap with the actor and its ShouldImpact returned false */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OverlappedByProjectile(AGRPrimitiveProjectile* Projectile, const FHitResult& HitResult);

    /** Executed when a projectile begin overlap with the actor and its ShouldImpact returned true */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImpactedByProjectile(AGRPrimitiveProjectile* Projectile, const FHitResult& HitResult);

    /** Executed when a projectile physically hit the actor (without overlapping) */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void HitByProjectile(AGRPrimitiveProjectile* Projectile, const FHitResult& HitResult);

    /** Executed when a projectile collided in any way with the actor */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void CollidedByProjectile(AGRPrimitiveProjectile* Projectile, const FHitResult& HitResult);

};
