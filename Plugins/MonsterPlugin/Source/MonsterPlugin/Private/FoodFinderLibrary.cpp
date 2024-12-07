// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#include "FoodFinderLibrary.h"
#include "Kismet/GameplayStatics.h"

AActor* UFoodFinderLibrary::GetClosestVisibleFood(const UObject* WorldContextObject, const FVector& CurrentLocation, float VisibilityRadius)
{
	TArray<AActor*> FoodActors;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, FoodActorTag, FoodActors);

	float DistanceToNearestActor;
	AActor* NearestActor = UGameplayStatics::FindNearestActor(CurrentLocation, FoodActors, DistanceToNearestActor);

	if (NearestActor == nullptr)
		return nullptr;

	if (DistanceToNearestActor < VisibilityRadius)
		return NearestActor;

	return nullptr;
}
