// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HungerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERPLUGIN_API UHungerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHungerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	float StomachSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	float EnergyLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
	float EnergyBurnRate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Monster")
	void Eat(float Energy);

	UFUNCTION(BlueprintCallable, Category = "Monster")
	bool IsHungry() const;
};
