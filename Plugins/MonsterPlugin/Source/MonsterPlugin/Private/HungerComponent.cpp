// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#include "HungerComponent.h"
#include "MonsterLog.h"

UHungerComponent::UHungerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	StomachSize = 1000.f;
	EnergyLevel = 100.f;
	EnergyBurnRate = 1.f;
}

void UHungerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHungerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float EnergySpent = EnergyBurnRate * DeltaTime;
	if (EnergyLevel > EnergySpent)
		EnergyLevel -= EnergySpent;
	else
	{
		EnergyLevel = 0.f;
		UE_LOG(LogTemp, Log, TEXT("Monster is dead :("));
		AActor* Owner = GetOwner();
		Owner->Destroy();
	}
}

void UHungerComponent::Eat(float NewEnergy)
{
	UE_LOG(MonsterLog, Log, TEXT("Monster is eating"));

	const float NewEnergyLevel = EnergyLevel + NewEnergy;
	EnergyLevel = NewEnergyLevel < StomachSize ? NewEnergyLevel : StomachSize;
}

bool UHungerComponent::IsHungry() const
{
	return EnergyLevel < 0.3f * StomachSize;
}

