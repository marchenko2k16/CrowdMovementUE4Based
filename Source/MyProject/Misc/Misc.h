#pragma once

// UE4
#include "CoreMinimal.h"

class Crowd;

namespace  Misc
{
	TArray<FVector> GetCrowdGoalPositions(const FVector& CrowdGoalPosition, const Crowd* Crowd);
	void SetCrowdMovementToPosition(const FVector& CrowdGoalPosition, Crowd* Crowd);

	float EuclidHeuristics(const FVector& First, const FVector& Second);
	float ManhattanHeuristics(const FVector& First, const FVector& Second);
}
