// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ExploreComponent.generated.h"

const float SquaredDistanceEpsilon = 100.f;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERPLUGIN_API UExploreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExploreComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	float VisionRadious;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	TObjectPtr<ATriggerVolume> GameVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	FVector Destination;

	FVector Direction;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Monster")
	const FVector& GenerateDestination();

	UFUNCTION(BlueprintCallable, Category = "Monster")
	const FVector& SetDestination(const FVector& NewDestination);

	UFUNCTION(BlueprintCallable, Category = "Monster")
	bool DestinationReached() const;

	void Walk(float DeltaTime);

private:
	FVector GetRandomLocationInArea() const;
};
