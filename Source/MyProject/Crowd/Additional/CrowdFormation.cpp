#include "Crowd/Additional/CrowdFormation.h"

CrowdFormation::CrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount)
{
}

CrowdFormation::~CrowdFormation()
{
	for (auto & AgentColumn : AgentPool)
	{
		AgentColumn.Reset();
	}
	AgentPool.Reset();
}
