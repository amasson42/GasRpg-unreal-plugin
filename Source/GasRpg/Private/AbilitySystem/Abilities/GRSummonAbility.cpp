// Amasson


#include "AbilitySystem/Abilities/GRSummonAbility.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
// #include "GameFramework/Actor.h"

UGRSummonAbility::UGRSummonAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

AActor* UGRSummonAbility::SummonActor(TSubclassOf<AActor> Class, const FVector& Location, float YawOffset)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
		return nullptr;

	AActor* Owner = GetOwningActorFromActorInfo();
	AActor* Avatar = GetAvatarActorFromActorInfo();

	FTransform SpawnTransform;
	
    SpawnTransform.SetLocation(Location);

    FVector SpawnDirection = Location - Avatar->GetActorLocation();
    SpawnDirection.Z = 0.0f;
    FRotator Rotation = UKismetMathLibrary::MakeRotFromX(SpawnDirection);
    Rotation.Yaw += YawOffset;

	SpawnTransform.SetRotation(Rotation.Quaternion());

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Owner;
	SpawnParameters.Instigator = Cast<APawn>(Avatar);
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AActor* Actor = GetWorld()->SpawnActor<AActor>(Class, SpawnTransform, SpawnParameters);

    if (!Actor)
        return nullptr;
    
    SpawnedActors.Add(Actor);

    Actor->OnDestroyed.AddDynamic(this, &UGRSummonAbility::SummonDestroyed);

    OnSpawnedActor.Broadcast(this, Actor);

	return Actor;
}

void UGRSummonAbility::SummonDestroyed(AActor* DestroyedActor)
{
    bool bRemovedOne = false;

    if (DestroyedActor)
    {
        if (SpawnedActors.RemoveSingle(DestroyedActor))
        {
            bRemovedOne = true;
        }
    }
    for (int32 i = SpawnedActors.Num() - 1; i >= 0; --i)
    {
        if (!IsValid(SpawnedActors[i]))
        {
            SpawnedActors.RemoveAt(i);
            bRemovedOne = true;
        }
    }
    if (bRemovedOne)
        OnActorDestroyed.Broadcast(this, DestroyedActor);
}

TArray<FVector> UGRSummonAbility::GetSpawnArcLocations()
{
    TArray<FVector> Locations;

    AActor* Avatar = GetAvatarActorFromActorInfo();

    FVector AvatarLocation = Avatar->GetActorLocation();
    FVector AvatarForward = Avatar->GetActorForwardVector();

    float StepAngle = SpawnSpreadAngle / (SpawnCount - 1);
    FVector Direction = SpawnCount == 1 ?
        AvatarForward :
        AvatarForward.RotateAngleAxis(-SpawnSpreadAngle / 2.0f, FVector::UpVector);

    for (int32 i = 0; i < SpawnCount; i++)
    {
        FVector Location = AvatarLocation + Direction * FMath::FRandRange(SpawnMinDistance, SpawnMaxDistance);
        Direction = Direction.RotateAngleAxis(StepAngle, FVector::UpVector);

        if (bProjectToNavigation)
        {
            FNavLocation NavLoc;
            UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
            if (!NavSystem->ProjectPointToNavigation(Location, NavLoc))
                continue;
            Location = NavLoc.Location;
        }
        
        Locations.Add(Location);
    }

    return Locations;
}
