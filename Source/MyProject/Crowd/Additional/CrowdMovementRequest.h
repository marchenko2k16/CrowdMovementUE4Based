#pragma once

#include "CoreMinimal.h"


class AAgent;
class CrowdFormation;

class CrowdMovementRequest
{
	TSharedPtr<CrowdFormation> Formation;
	FVector GoalLocation = FVector::ZeroVector;

	float RequestTimestamp = 0.f;
	int32 LastProcessedColumnIndex = 0;

public:

	void SetGoalLocation(const FVector& InGoalLocation);
	void SetRequestTimestamp(float Timestamp);
	void SetFormation(TSharedPtr<CrowdFormation> InFormation);

	TArray<AAgent*>& GetNextUnprocessedFormationColumn() const;
	TArray<FVector>& GetNextUnprocessedLocations() const;
	
	FVector GetGoalLocation() const;

	// todo : am : make it beautiful somehow
	void MarkProcessedCurrentFormationColumn();

	bool HasProcessedRequest() const;
};