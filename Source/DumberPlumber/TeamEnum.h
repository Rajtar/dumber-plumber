#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"

UENUM(BlueprintType)
enum class ETeamEnum : uint8
{
	UNDEFINED UMETA(DisplayName = "UNDEFINED"),
	BLUE      UMETA(DisplayName = "BLUE"),
	RED       UMETA(DisplayName = "RED")
};
