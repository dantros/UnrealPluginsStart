// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FoodFinderLibrary.h"
#include "FoodComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERPLUGIN_API UFoodComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFoodComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	float EnergyStored;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
