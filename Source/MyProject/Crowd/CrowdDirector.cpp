#include "Crowd/CrowdDirector.h"
#include "Crowd/Agent.h"

#include "Algo/AStarSolver.h"
#include "Algo/GraphNode.h"
#include "Algo/Grid.h"
#include "Algo/GridGenerator.h"
#include "Algo/Path.h"

#include "MyProjectGameMode.h"

// UE4
#include "NavigationSystem.h"

void ACrowdDirector::BeginPlay()
{
	Super::BeginPlay();
	UNavigationSystemV1::NavigationDirtyEvent.AddUObject(this, &ACrowdDirector::OnNavigationUpdate);
}

ACrowdDirector::ACrowdDirector()
{
	PrimaryActorTick.bCanEverTick = true;
}

ACrowdDirector::~ACrowdDirector()
{}

void ACrowdDirector::SetDirectedCrowd(Crowd* InDirectedCrowd)
{
	DirectedCrowd = InDirectedCrowd;
}

void ACrowdDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProcessCrowdMovementRequest();
}

void ACrowdDirector::ProcessCrowdMovementRequest()
{
	//if (!MovementRequest.IsValid())
	if (!MovementRequest)
	{
		return;
	}

	if (MovementRequest->HasProcessedRequest())
	{
		//constexpr float TimeToPassSec = 1.7f;
		constexpr float TimeToPassSec = 1.f;
		const float CurrentTime = GetWorld()->GetRealTimeSeconds();
		if (LastRequestProcessedTimestamp>=CurrentTime-TimeToPassSec )
		{
			return;
		}
		LastRequestProcessedTimestamp = CurrentTime;

		ProcessCrowdColumnMovementRequest();
		MovementRequest->MarkProcessedCurrentFormationRow();
	}
	else
	{
		MovementRequest.Reset();
		MovementRequest = nullptr;
	}
}

void ACrowdDirector::AddMovementRequest(TSharedPtr<CrowdMovementRequest> InMovementRequest)
{
	// todo : am : 
	//MovementRequest = MakeUnique<CrowdMovementRequest>(InMovementRequest);
	MovementRequest = InMovementRequest;
}

void ACrowdDirector::ProcessCrowdColumnMovementRequest()
{
	const auto CurrentUnprocessedCrowdColumn = MovementRequest->GetNextUnprocessedFormationRow();
	const auto ColumnGoalLocations = MovementRequest->GetNextUnprocessedLocations();

	SetCrowdColumnMovement(CurrentUnprocessedCrowdColumn, ColumnGoalLocations);
}

void ACrowdDirector::SetCrowdColumnMovement(const TArray<AAgent*>& CurrentUnprocessedCrowdColumn,
                                            const TArray<FVector>& ColumnGoalLocations) const
{
	for (int32 Index = CurrentUnprocessedCrowdColumn.Num()-1; Index>=0; Index--)
	{
		const auto Agent = CurrentUnprocessedCrowdColumn[Index];
		const auto AgentLocation = Agent->GetActorLocation();
		const auto GoalLocation = MovementRequest->GetGoalLocation()+ColumnGoalLocations[Index];

		SetAgentMovement(Agent, AgentLocation, GoalLocation);
	}
}

void ACrowdDirector::SetAgentMovement(AAgent* Agent, const FVector& AgentLocation, const FVector& GoalLocation) const
{
	// todo : am : it should be performed on higher abstraction level
	const EMovementRequestType PathFollowingType = EMovementRequestType::AStarDelay;
	switch (PathFollowingType)
	{
		case EMovementRequestType::AStarDelay:
		{
			PerformAStarMovement(AgentLocation, GoalLocation, Agent);
			break;
		}
		default:
		{
			break;
		}
	}
}

void ACrowdDirector::PerformAStarMovement(const FVector& AgentLocation, const FVector& GoalLocation, AAgent* Agent) const
{
	AStarSolver PathFinder;
	const auto Grid = AMyProjectGameMode::GetGridGenerator()->GetGlobalGridData();

	const auto StartNode = AMyProjectGameMode::GetGridGenerator()->GetGraphNodeByLocation(AgentLocation);
	const auto GoalNode = AMyProjectGameMode::GetGridGenerator()->GetGraphNodeByLocation(GoalLocation);

	const auto SearchResult = PathFinder.FindPath(Grid, StartNode, GoalNode, Agent);
	Path* AgentPath = SearchResult.Get<1>();

	Agent->SetPath(AgentPath);

	const auto& NextNode = AgentPath->GetNextGraphNode();
	if (!NextNode)
	{
		return;
	}
	Agent->MoveToLocation(NextNode->GetLocation());
}

void ACrowdDirector::SerializePath(Path* Path)
{
	AgentPaths.Emplace(Path->PathOwner->GetAgentIndex(), Path);
}

Path* ACrowdDirector::GetSerializedPath(int32 AgentID)
{
	if (!AgentPaths.Contains(AgentID))
	{
		return nullptr;
	}
	return AgentPaths[AgentID];
}

void ACrowdDirector::SetCrowdMovement(FVector)
{}

void ACrowdDirector::OnNavigationUpdate(const FBox& Bounds)
{
	ReorganizeCrowdMovement();
}

void ACrowdDirector::ReorganizeCrowdMovement()
{
	int32 DebugVar = 0;
}

void ACrowdDirector::UpdateSerializedPathes()
{}

void ACrowdDirector::BeginDestroy()
{
	Super::BeginDestroy();
	if (MovementRequest)
	{
		MovementRequest.Reset();
		MovementRequest = nullptr;
	}
}
