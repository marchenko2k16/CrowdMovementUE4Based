#include "Misc/Misc.h"
#include "Crowd/Crowd.h"
#include "Crowd/Agent.h"

TArray<FVector> Misc::GetCrowdGoalPositions(const FVector& CrowdGoalPosition, const Crowd* Crowd)
{
	TArray<FVector> GoalLocations;
	const FVector MassCenter = Crowd->GetMassCenter();

	for (auto & Agent : Crowd->GetAgentPoolConst())
	{

		const FVector AgentOffset = Agent->GetLocation() - MassCenter;

		GoalLocations.Emplace(CrowdGoalPosition + AgentOffset);
	}

	return GoalLocations;
}

void Misc::SetCrowdMovementToPosition(const FVector& CrowdGoalPosition, Crowd* Crowd)
{
	const auto GoalLocations = GetCrowdGoalPositions(CrowdGoalPosition, Crowd);
	Crowd->SetCrowdMovementGoal(GoalLocations);
}

float Misc::EuclidHeuristics(const FVector& First, const FVector& Second)
{
	return FVector::Dist(Second,First);
}

float Misc::ManhattanHeuristics(const FVector& First, const FVector& Second)
{
	return FMath::Abs(Second.X - First.X) + FMath::Abs(Second.Y - First.Y);
}