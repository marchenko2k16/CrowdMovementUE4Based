#include "Crowd/Additional/CrowdMovementRequest.h"
#include "Crowd/Additional/CrowdFormation.h"
#include "Crowd/Agent.h"

void CrowdMovementRequest::SetCrowdMovementGoalLocation(const FVector& InGoalLocation)
{
	GoalLocation = InGoalLocation;
}

void CrowdMovementRequest::SetCrowdMovementRequestTimestamp(float Timestamp)
{
	RequestTimestamp = Timestamp;
}

TArray<AAgent*>& CrowdMovementRequest::GetNextUnprocessedFormationColumn() const
{
	return Formation->GetAgentPoolMutable()[LastProcessedColumnIndex];
}

TArray<FVector>& CrowdMovementRequest::GetNextUnprocessedLocations() const
{
	return Formation->GetOffsetsMutable()[LastProcessedColumnIndex];
}

FVector CrowdMovementRequest::GetGoalLocation() const
{
	return GoalLocation;
}

void CrowdMovementRequest::MarkProcessedCurrentFormationColumn()
{
	LastProcessedColumnIndex++;
}

bool CrowdMovementRequest::HasProcessedRequest() const
{
	return Formation->GetOffsetsMutable().Num() >= LastProcessedColumnIndex;
}
