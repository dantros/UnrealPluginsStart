// 4D Runtime Tutorial - https://www.youtube.com/@4druntime

#pragma once

#include "MonsterState.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle = 0			UMETA(DisplayName = "Idle"),
	Hungry				UMETA(DisplayName = "Hungry"),
	Exploring			UMETA(DisplayName = "Exploring"),
	MovingTowardsFood	UMETA(DisplayName = "MovingTowardsFood")
};

