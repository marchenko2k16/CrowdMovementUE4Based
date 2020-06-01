#include "Crowd/Crowd.h"
#include "Crowd/Agent.h"

#include "Crowd/Additional/CrowdMovementRequest.h"
#include "Crowd/AgentSpawner.h"

// ue4
#include "Engine/World.h"

Crowd::Crowd()
{}

Crowd::~Crowd()
{
	// todo : am : try to find way to make shared
	//delete Formation;
}

void Crowd::ReinitializeCrowdDirector()
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

//void Crowd::SetCrowdFormation(CrowdFormation* InFormation)
void Crowd::SetCrowdFormation(TSharedPtr<CrowdFormation> InFormation)
{
	Formation = InFormation;
	//Formation = MakeShared<CrowdFormation>(*InFormation);
}

void Crowd::RequestMovementToGoal(const FVector& GoalLocation)
{
	// todo : am : refactor and find simplier way

	if (!Formation)
	{
		return;
	}

	UWorld* World = Formation->GetAgentPoolMutable()[0][0]->GetWorld();

	TSharedPtr<CrowdMovementRequest> MovementRequest = MakeShared<CrowdMovementRequest>();
	MovementRequest->SetGoalLocation(GoalLocation);
	MovementRequest->SetRequestTimestamp(World->GetTimeSeconds());
	MovementRequest->SetFormation(Formation);
	//TUniquePtr<CrowdMovementRequest> MovementRequest = );
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
