#pragma once

#include "CoreMinimal.h"


namespace Constants
{
	const FVector DebugVectorZOffset{0.f, 0.f, 200.f};
	const float GridStep = 100.f;
	const float HalfGridStep = GridStep / 2.f;
	const float BaseStepCost = 1.f;
	const float NonTraversableNeighborIncreasingCost = 5.f;
}