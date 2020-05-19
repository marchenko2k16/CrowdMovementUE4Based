#pragma once

#include "CoreMinimal.h"
#include "StrongObjectPtr.h"

class AAgent;

class ACrowdDirector;

class Crowd
{
private:
	class CrowdFormation* Formation = nullptr;
	
protected:

	TStrongObjectPtr<ACrowdDirector> CrowdDirector;
	
public:

	Crowd();
	~Crowd();

	void ReinitCrowdDirector();

	TArray<AAgent*>& GetAgentPoolMutable();
	const TArray<AAgent*>& GetAgentPoolConst() const;
	void SetAgentPool(TArray<AAgent*> InAgents);

	void SetCrowdMovementGoal(const FVector& GoalLocation);
	void SetCrowdMovementGoal(const TArray<FVector>& GoalLocations);
	void AbortCrowdMovementMovement();

	void Init();
	
	FVector GetMassCenter() const;
};