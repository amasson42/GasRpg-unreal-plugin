// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/GRPrimitiveProjectile.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"

AGRPrimitiveProjectile::AGRPrimitiveProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 60.0f;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.0f;
	ProjectileMovement->MaxSpeed = 550.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComponent->SetupAttachment(GetRootComponent());
}

void AGRPrimitiveProjectile::BeginPlay()
{
	Super::BeginPlay();

}

bool AGRPrimitiveProjectile::ShouldImpact_Implementation(const FHitResult& HitResult)
{
	return GetInstigator() != HitResult.GetActor();
}

void AGRPrimitiveProjectile::DidImpact_Implementation(const FHitResult& HitResult)
{
	ApplyEffectsToHitResult(HitResult);
}

void AGRPrimitiveProjectile::DidOverlap_Implementation(const FHitResult& HitResult)
{
	
}

void AGRPrimitiveProjectile::DidHit_Implementation(const FHitResult& HitResult)
{
    
}

void AGRPrimitiveProjectile::DidAnyCollision_Implementation(const FHitResult& HitResult)
{
    
}

void AGRPrimitiveProjectile::OnPrimitiveOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
 
    bool bHitActorImplementsInterface = IsValid(HitActor) && HitActor->GetClass()->ImplementsInterface(UProjectileReactionInterface::StaticClass());

	if (ShouldImpact(HitResult))
	{
		if (bHitActorImplementsInterface)
		    IProjectileReactionInterface::Execute_ImpactedByProjectile(HitActor, this, HitResult);
		OnImpact.Broadcast(this, HitResult);
		DidImpact(HitResult);
	}
	else
	{
		if (bHitActorImplementsInterface)
			IProjectileReactionInterface::Execute_OverlappedByProjectile(HitActor, this, HitResult);
		OnOverlap.Broadcast(this, HitResult);
        DidOverlap(HitResult);
	}

    if (bHitActorImplementsInterface)
        IProjectileReactionInterface::Execute_CollidedByProjectile(HitActor, this, HitResult);
    OnAnyCollision.Broadcast(this, HitResult);
    DidAnyCollision(HitResult);
}

void AGRPrimitiveProjectile::OnPrimitiveHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
    AActor* HitActor = HitResult.GetActor();

    bool bHitActorImplementsInterface = IsValid(HitActor) && HitActor->GetClass()->ImplementsInterface(UProjectileReactionInterface::StaticClass());

    if (bHitActorImplementsInterface)
        IProjectileReactionInterface::Execute_HitByProjectile(HitActor, this, HitResult);
    OnHit.Broadcast(this, HitResult);
    DidHit(HitResult);

    if (bHitActorImplementsInterface)
        IProjectileReactionInterface::Execute_CollidedByProjectile(HitActor, this, HitResult);
    OnAnyCollision.Broadcast(this, HitResult);
    DidAnyCollision(HitResult);
}
