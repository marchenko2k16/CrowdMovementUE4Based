#pragma once

#include "CoreMinimal.h"


#include "Additional/CrowdFormation.h"
#include "Crowd/CrowdDirector.h"

// ue4
#include "StrongObjectPtr.h"

class AAgent;

//class ACrowdDirector;
//class CrowdFormation;

struct Path;

class Crowd
{
private:
	// todo : am : try to find way to make shared
	TSharedPtr<CrowdFormation> Formation = nullptr;
	//CrowdFormation* Formation = nullptr;
	
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

	//void SetCrowdFormation(CrowdFormation* InFormation);
	void SetCrowdFormation(TSharedPtr<CrowdFormation> InFormation);

	void RequestMovementToGoal(const FVector& GoalLocation);
	void AbortCrowdMovement(); // todo : am : mb add soft/hard stop

	FVector GetCrowdMassCenter() const;
};