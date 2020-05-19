#include "Crowd.h"
#include "Agent.h"

#include "AgentSpawner.h"

#include "Algo/Path.h"
#include "Algo/GraphNode.h"

#include "CrowdDirector.h"

#include "Algo/AStarSolver.h"
#include "Algo/GridGenerator.h"

#include "MyProjectGameMode.h"

#include "Crowd/Additional/CrowdFormation.h"

Crowd::Crowd()
{
	//UWorld::GetWorld()
	//UGameplayStatics::GetGameMode();
	// TODO Finish
}

Crowd::~Crowd()
{
	delete Formation;
	//AgentPool.Reset();
	//for (const auto & Agent : AgentPool)
	//{
	//	delete Agent;
	//}
}

void Crowd::ReinitCrowdDirector()
{
	ACrowdDirector* LocalCrowdDirector = AAgentSpawner::SpawnCrowdDirector(AgentPool.Last()->GetWorld());

	if (!LocalCrowdDirector)
	{
		return;
	}
	CrowdDirector.Reset(LocalCrowdDirector);
	CrowdDirector->SetDirectedCrowd(this);
}

TArray<AAgent*>& Crowd::GetAgentPoolMutable()
{
	return AgentPool;
}

const TArray<AAgent*>& Crowd::GetAgentPoolConst() const
{
	return AgentPool;
}

void Crowd::SetAgentPool(TArray<AAgent*> InAgents)
{
	AgentPool = InAgents;
}

void Crowd::SetCrowdMovementGoal(const FVector& GoalLocation)
{
	//TArray<FVector> GoalLocations = GenerateLocationPointsNearGoalLocation(GoalLocation);
	//SetCrowdMovementGoal(GoalLocations);
	for (const auto& CrowdAgent : AgentPool)
	{
		CrowdAgent->MoveToLocation(GoalLocation);
	}
}

void Crowd::SetCrowdMovementGoal(const TArray<FVector>& GoalLocations)
{
	AStarSolver PathSolver;
	const auto Grid = AMyProjectGameMode::GetGridGenerator()->GetGlobalGridData();

	const auto PositionsCount = GoalLocations.Num();

	for(int32 Index = 0; Index < PositionsCount; Index++)
	{
		const auto GoalLocationNode = AMyProjectGameMode::GetGridGenerator()->GetGraphNodeByLocation(GoalLocations[Index]);
		const auto CurrentAgentLocation = AgentPool[Index]->GetLocation();
		const auto PlayerLocationNode = AMyProjectGameMode::GetGridGenerator()->GetGraphNodeByLocation(CurrentAgentLocation);
		

		const auto SearchResult = PathSolver.FindPath(Grid, PlayerLocationNode, GoalLocationNode, AgentPool[Index]);
		Path* AgentPath = SearchResult.Get<1>();

		AgentPool[Index]->SetPath(AgentPath);
		const auto& NextNode = AgentPath->GetNextGraphNode();
		if (!NextNode)
		{
			continue;
		}
		AgentPool[Index]->MoveToLocation(NextNode->GetLocation());
	}
}

void Crowd::AbortCrowdMovementMovement()
{
	for (const auto& CrowdAgent : AgentPool)
	{
		if (CrowdAgent->IsValidLowLevel())
		{
			CrowdAgent->AbortMovement();
		}
	}
}

void Crowd::Init()
{}

FVector Crowd::GetMassCenter() const
{
	FVector MassCenter = FVector::ZeroVector;

	const int32 AgentsCount = AgentPool.Num();
	if (AgentsCount<=0)
	{
		return MassCenter;
	}

	for (const auto& CrowdAgent : AgentPool)
	{
		MassCenter += CrowdAgent->GetLocation();
	}

	MassCenter /= AgentsCount;
	return MassCenter;
}
