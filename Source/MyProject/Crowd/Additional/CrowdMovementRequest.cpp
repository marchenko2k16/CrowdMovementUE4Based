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

TArray<AAgent*>& CrowdMovementRequest::GetNextUnprocessedFormationRow() const
{
	return Formation->GetAgentPoolMutable()[LastProcessedRowIndex];
}

TArray<FVector>& CrowdMovementRequest::GetNextUnprocessedLocations() const
{
	return Formation->GetOffsetsMutable()[LastProcessedRowIndex];
}

FVector CrowdMovementRequest::GetGoalLocation() const
{
	return GoalLocation;
}

void CrowdMovementRequest::MarkProcessedCurrentFormationRow()
{
	LastProcessedRowIndex++;
}

bool CrowdMovementRequest::HasProcessedRequest() const
{
	return LastProcessedRowIndex<Formation->GetOffsetsMutable().Num();
}
