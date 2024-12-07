// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#include "FoodComponent.h"

UFoodComponent::UFoodComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	EnergyStored = 10.f;
}

void UFoodComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	check(Owner);
	Owner->Tags.Add(FoodActorTag);
}

void UFoodComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

