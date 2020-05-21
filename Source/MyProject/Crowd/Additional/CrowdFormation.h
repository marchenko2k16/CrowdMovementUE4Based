#pragma once

#include "CoreMinimal.h"

class AAgent;

// TODO : AM : Decide to return FVector either by ref or by value
class CrowdFormation
{
protected:
	friend class AAgentSpawner;

	TArray<TArray<FVector>> Offsets;
	TArray<TArray<AAgent*>> AgentPool;

	FVector CrowdCenter = FVector::ZeroVector;
	int32 MembersCount = -1;

public:
	CrowdFormation(FVector InCrowdCenter, int32 InCrowdMembersCount);
	virtual ~CrowdFormation();

	TArray<TArray<FVector>>& GetOffsetsMutable();
	TArray<TArray<AAgent*>>& GetAgentPoolMutable();

	FVector GetCenter() const;
	int32 GetCount() const;

	virtual void GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount);
};
