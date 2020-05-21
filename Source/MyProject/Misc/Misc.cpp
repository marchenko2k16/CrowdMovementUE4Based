#include "Misc/Misc.h"
#include "Crowd/Crowd.h"
#include "Crowd/Agent.h"

// todo : am : add heuristic class
float Misc::EuclidHeuristics(const FVector& First, const FVector& Second)
{
	return FVector::Dist(Second,First);
}

float Misc::ManhattanHeuristics(const FVector& First, const FVector& Second)
{
	return FMath::Abs(Second.X - First.X) + FMath::Abs(Second.Y - First.Y);
}