// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "ExploreComponent.h"
#include "HungerComponent.h"
#include "MonsterState.h"
#include "Monster.generated.h"

UCLASS()
class MONSTERPLUGIN_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonster();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	TObjectPtr<UExploreComponent> ExploreComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	TObjectPtr<UHungerComponent> HungerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Monster")
	EMonsterState MonsterState;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void SetState(EMonsterState NewMonsterState);
};
