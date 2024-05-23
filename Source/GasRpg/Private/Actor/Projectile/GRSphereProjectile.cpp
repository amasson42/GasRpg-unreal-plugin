// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/GRSphereProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"

AGRSphereProjectile::AGRSphereProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

	ArrowComponent->SetupAttachment(Sphere);
}

void AGRSphereProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
    {
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPrimitiveOverlap);
        Sphere->OnComponentHit.AddDynamic(this, &ThisClass::OnPrimitiveHit);
    }
}

void AGRSphereProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
    Super::OnPrimitiveOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitResult);
}

void AGRSphereProjectile::OnSphereHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
    Super::OnPrimitiveHit(OverlappedComponent, OtherActor, OtherComponent, NormalImpulse, HitResult);
}
