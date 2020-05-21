#pragma once

// UE4
#include "CoreMinimal.h"

class Crowd;

namespace  Misc
{
	float EuclidHeuristics(const FVector& First, const FVector& Second);
	float ManhattanHeuristics(const FVector& First, const FVector& Second);
}
