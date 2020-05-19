#pragma once

#include "CoreMinimal.h"

class AAgent;

class CrowdFormation
{
private:
	FVector Center = FVector::ZeroVector;
	int32 CrowdMemberCount = -1;

public:
	CrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount);
	virtual ~CrowdFormation();

	TArray<TArray<FVector>> Offsets;
	TArray<TArray<AAgent*>> AgentPool;
	
	//virtual TArray<FVector> GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) = 0;
};
