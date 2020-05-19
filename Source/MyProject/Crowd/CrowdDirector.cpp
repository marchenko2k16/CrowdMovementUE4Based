#include "CrowdDirector.h"
#include "Algo/Path.h"
#include "Crowd/Agent.h"

void ACrowdDirector::BeginPlay()
{
	Super::BeginPlay();
	UNavigationSystemV1::NavigationDirtyEvent.AddUObject(this, &ACrowdDirector::OnNavigationUpdate);
}

void ACrowdDirector::SetDirectedCrowd(Crowd* InDirectedCrowd)
{
	DirectedCrowd = InDirectedCrowd;
}

void ACrowdDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
{
}

void ACrowdDirector::ReorganizeCrowdMovement()
{
	int32 DebugVar = 0;
}

void ACrowdDirector::UpdatePathMap()
{
}

void ACrowdDirector::BeginDestroy()
{
	Super::BeginDestroy();
}
