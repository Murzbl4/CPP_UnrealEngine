

#pragma once


#include "EFireModeEnum.generated.h"

UENUM(BlueprintType)
enum class EFireModeEnum : uint8
{
	EFireModeEnum1 UMETA(DisplayName = "Auto"),
	EFireModeEnum2 UMETA(DisplayName = "Semi"),
	EFireModeEnum3 UMETA(DisplayName = "Burst"),
	EFireModeEnum4 UMETA(DisplayName = "Nothing"),
};