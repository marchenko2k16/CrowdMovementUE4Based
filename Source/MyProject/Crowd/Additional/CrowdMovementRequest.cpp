#include "Crowd/Additional/CrowdMovementRequest.h"
#include "Crowd/Additional/CrowdFormation.h"
#include "Crowd/Agent.h"

void CrowdMovementRequest::SetGoalLocation(const FVector& InGoalLocation)
{
	GoalLocation = InGoalLocation;
}

void CrowdMovementRequest::SetRequestTimestamp(float Timestamp)
{
	RequestTimestamp = Timestamp;
}

void CrowdMovementRequest::SetFormation(TSharedPtr<CrowdFormation> InFormation)
{
	Formation = InFormation;
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
	return LastProcessedColumnIndex<Formation->GetOffsetsMutable().Num();
}
