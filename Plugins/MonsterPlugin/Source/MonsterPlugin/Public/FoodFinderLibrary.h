// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FoodFinderLibrary.generated.h"

// This is used to identify any actor that will have this component.
// Do not use the same tag for anything else, or use here anything that is unique.
const FName FoodActorTag(TEXT("FoodActor"));

UCLASS()
class MONSTERPLUGIN_API UFoodFinderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Monster")
	static AActor* GetClosestVisibleFood(const UObject* WorldContextObject, const FVector& CurrentLocation, float VisibilityRadius);
};
