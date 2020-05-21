#pragma once

#include "CoreMinimal.h"
#include "StrongObjectPtr.h"

class AAgent;
class ACrowdDirector;
class CrowdFormation;

class Path;

class Crowd
{
private:
	TSharedPtr<CrowdFormation> Formation = nullptr;
	
protected:

	TStrongObjectPtr<ACrowdDirector> CrowdDirector;
	
public:

	Crowd();
	~Crowd();

	void ReinitCrowdDirector();

	TArray<TArray<AAgent*>>& GetAgentPoolMutable();
	TArray<TArray<AAgent*>>& GetAgentPoolConst() const;

	TArray<TArray<FVector>>& GetCrowdOffsetsMutable() const;
	TArray<TArray<FVector>>& GetCrowdOffsetsConst() const;

	void SetCrowdFormation(CrowdFormation* InFormation);

	void RequestMovementToGoal(const FVector& GoalLocation);
	void AbortCrowdMovement(); // todo : am : mb add soft/hard stop

	FVector GetCrowdMassCenter() const;
};