#include "Crowd/Additional/CrowdFormation.h"

CrowdFormation::CrowdFormation(FVector InCrowdCenter, int32 InCrowdMembersCount)
{
	CrowdCenter = InCrowdCenter;
	MembersCount = InCrowdMembersCount;
}

CrowdFormation::~CrowdFormation()
{
	for (auto& AgentColumn : AgentPool)
	{
		AgentColumn.Reset();
	}
	AgentPool.Reset();
}

TArray<TArray<FVector>>& CrowdFormation::GetOffsetsMutable()
{
	return Offsets;
}

TArray<TArray<AAgent*>>& CrowdFormation::GetAgentPoolMutable()
{
	return AgentPool;
}

FVector CrowdFormation::GetCenter() const
{
	return CrowdCenter;
}

int32 CrowdFormation::GetCount() const
{
	return MembersCount;
}

void CrowdFormation::GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount)
{
	ensure("should never be called");
}
