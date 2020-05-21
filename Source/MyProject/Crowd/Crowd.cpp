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
#include "Crowd/Additional/CrowdMovementRequest.h"
#include "AITestSuite/Public/AITestsCommon.h"

Crowd::Crowd()
{}

Crowd::~Crowd()
{
	delete Formation;
}

void Crowd::ReinitCrowdDirector()
{
	ACrowdDirector* LocalCrowdDirector = AAgentSpawner::SpawnCrowdDirector(Formation->GetAgentPoolMutable().Last().Last()->GetWorld());

	if (!LocalCrowdDirector)
	{
		return;
	}
	CrowdDirector.Reset(LocalCrowdDirector);
	CrowdDirector->SetDirectedCrowd(this);
}

TArray<TArray<AAgent*>>& Crowd::GetAgentPoolMutable()
{
	return Formation->GetAgentPoolMutable();
}

TArray<TArray<AAgent*>>& Crowd::GetAgentPoolConst() const
{
	return Formation->GetAgentPoolMutable();
}

TArray<TArray<FVector>>& Crowd::GetCrowdOffsetsMutable() const
{
	return Formation->GetOffsetsMutable();
}

TArray<TArray<FVector>>& Crowd::GetCrowdOffsetsConst() const
{
	return Formation->GetOffsetsMutable();
}

void Crowd::SetCrowdFormation(CrowdFormation* InFormation)
{
	Formation = MakeShared<CrowdFormation>(InFormation);
}

void Crowd::RequestMovementToGoal(const FVector& GoalLocation)
{
	CrowdMovementRequest* MovementRequest = nullptr;

	// todo : am : refactor 
	const auto AIHelperWorld = FAITestHelpers::GetWorld();
	const auto World = Formation->GetAgentPoolMutable()[0][0]->GetWorld();
	if (AIHelperWorld==World)
	{
		int j = 134;
	}

	MovementRequest->SetCrowdMovementGoalLocation(GoalLocation);
	MovementRequest->SetCrowdMovementRequestTimestamp(World->GetTimeSeconds());
	CrowdDirector->AddMovementRequest(MovementRequest);
}

void Crowd::AbortCrowdMovement()
{
	for (const auto& CrowdFormationColumn : Formation->GetAgentPoolMutable())
	{
		for (const auto& Agent : CrowdFormationColumn)
		{
			if (Agent->IsValidLowLevel())
			{
				Agent->AbortMovement();
			}
		}
	}
}

FVector Crowd::GetCrowdMassCenter() const
{
	FVector MassCenter = FVector::ZeroVector;

	const int32 AgentsCount = Formation->GetCount();
	if (AgentsCount<=0)
	{
		return MassCenter;
	}

	for (const auto& CrowdFormationColumn : Formation->GetAgentPoolMutable())
	{
		for (const auto& Agent : CrowdFormationColumn)
		{
			if (Agent->IsValidLowLevel())
			{
				MassCenter += Agent->GetActorLocation();
			}
		}
	}

	MassCenter /= AgentsCount;
	return MassCenter;
}
