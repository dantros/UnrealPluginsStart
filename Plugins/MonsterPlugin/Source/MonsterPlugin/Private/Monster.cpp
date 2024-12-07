// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#include "Monster.h"
#include "FoodComponent.h"
#include "FoodFinderLibrary.h"
#include "MonsterLog.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	Name = TEXT("Unnamed Monster");

	ExploreComponent = CreateDefaultSubobject<UExploreComponent>(TEXT("ExploreComponent"));
	HungerComponent = CreateDefaultSubobject<UHungerComponent>(TEXT("HungerComponent"));

	MonsterState = EMonsterState::Idle;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(HungerComponent);
	check(ExploreComponent);

	switch (MonsterState)
	{
	case EMonsterState::Idle:
	{
		if (HungerComponent->IsHungry())
		{
			SetState(EMonsterState::Hungry);
		}
		else
		{
			ExploreComponent->GenerateDestination();
			SetState(EMonsterState::Exploring);
		}
	}
	break;
	case EMonsterState::Hungry:
	{
		AActor* ClosestVisibleFood = UFoodFinderLibrary::GetClosestVisibleFood(GetWorld(), GetActorLocation(), ExploreComponent->VisionRadious);
		if (ClosestVisibleFood != nullptr)
		{
			FVector FoodLocation = ClosestVisibleFood->GetActorLocation();
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
					FString::Printf(TEXT("%s found food at %s"), *Name, *FoodLocation.ToString()));
			ExploreComponent->SetDestination(FoodLocation);
			SetState(EMonsterState::MovingTowardsFood);
		}
		else
		{
			ExploreComponent->GenerateDestination();
			SetState(EMonsterState::Exploring);
		}
	}
	break;
	case EMonsterState::Exploring:
	{
		ExploreComponent->Walk(DeltaTime);
		if (ExploreComponent->DestinationReached())
			SetState(EMonsterState::Idle);
	}
	break;
	case EMonsterState::MovingTowardsFood:
	default:
	{
		ExploreComponent->Walk(DeltaTime);
		if (not ExploreComponent->DestinationReached())
			break;
		
		AActor* ClosestVisibleFood = UFoodFinderLibrary::GetClosestVisibleFood(GetWorld(), GetActorLocation(), 2.f * SquaredDistanceEpsilon);
		if (ClosestVisibleFood == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Someone ate %s food!!"), *Name);
		}
		else
		{
			UFoodComponent* FoodComponent = ClosestVisibleFood->GetComponentByClass<UFoodComponent>();
			// something is completely wrong if there is no a UFoodComponent. Check FoodActorTag 
			check(FoodComponent);
			HungerComponent->Eat(FoodComponent->EnergyStored);
			ClosestVisibleFood->Destroy();
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
					FString::Printf(TEXT("%s has eaten! New Energy Level: %f"), *Name, HungerComponent->EnergyLevel));
		}
		SetState(EMonsterState::Idle);
	}
	break;
	};
}

void AMonster::SetState(EMonsterState NewMonsterState)
{
	static const UEnum* Enum = StaticEnum<EMonsterState>();

	FString OldMonsterStateString = Enum->GetNameStringByValue(static_cast<int>(MonsterState));
	FString NewMonsterStateString = Enum->GetNameStringByValue(static_cast<int>(NewMonsterState));

	UE_LOG(MonsterLog, Log, TEXT("%s state transition: [%d] %s -> [%d] %s"), *Name,
		static_cast<int>(MonsterState), *OldMonsterStateString,
		static_cast<int>(NewMonsterState), *NewMonsterStateString);

	MonsterState = NewMonsterState;
}

