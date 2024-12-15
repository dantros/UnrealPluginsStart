// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#include "ExploreComponent.h"
#include "MonsterLog.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterLog.h"

// Sets default values for this component's properties
UExploreComponent::UExploreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	VisionRadious = 1000.f;
	Speed = 100.f;
}

FVector UExploreComponent::GetRandomLocationInArea() const
{
	TArray<AActor*> Actors;
	Actors.Add(GameVolume);
	FVector Center, BoxExtent;
	UGameplayStatics::GetActorArrayBounds(Actors, false, Center, BoxExtent);

	const FVector MinCorner = Center - BoxExtent / 2.f;
	const FVector MaxCorner = Center + BoxExtent / 2.f;
	const float RandomX = FMath::RandRange(MinCorner.X, MaxCorner.X);
	const float RandomY = FMath::RandRange(MinCorner.Y, MaxCorner.Y);
	return FVector(RandomX, RandomY, 0.f);
}

void UExploreComponent::BeginPlay()
{
	Super::BeginPlay();

	FVector RandomStartLocation = GetRandomLocationInArea();
	AActor* Owner = GetOwner();
	Owner->SetActorLocation(RandomStartLocation);
}

void UExploreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

const FVector& UExploreComponent::GenerateDestination()
{
	FVector NewDestination = GetRandomLocationInArea();

	AActor* Owner = GetOwner();
	FVector OwnerLocation = Owner->GetActorLocation();
	if (FVector::Distance(OwnerLocation, NewDestination) > VisionRadious)
	{
		FVector DisplacementDirection = NewDestination - OwnerLocation;
		DisplacementDirection.Normalize();
		NewDestination = OwnerLocation + (DisplacementDirection * VisionRadious);
	}

	UE_LOG(MonsterLog, Log, TEXT("GenerateDestination=%s"), *NewDestination.ToString());
	return SetDestination(NewDestination);
}

const FVector& UExploreComponent::SetDestination(const FVector& NewDestination)
{
	Destination = NewDestination;
	AActor* Owner = GetOwner();
	FVector OwnerLocation = Owner->GetActorLocation();
	Direction = Destination - OwnerLocation;
	Direction.Normalize();
	UE_LOG(MonsterLog, Log, TEXT("SetDestination: Destination=%s ; Direction=%s"), *Destination.ToString(), *Direction.ToString());
	return Destination;
}

bool UExploreComponent::DestinationReached() const
{
	AActor* Owner = GetOwner();
	FVector OwnerLocation = Owner->GetActorLocation();
	return FVector::DistSquared(OwnerLocation, Destination) < SquaredDistanceEpsilon;
}

void UExploreComponent::Walk(float DeltaTime)
{
	AActor* Owner = GetOwner();
	FVector OwnerLocation = Owner->GetActorLocation();
	const FVector NewLocation = OwnerLocation + (Speed * DeltaTime * Direction);
	Owner->SetActorLocation(NewLocation);
}