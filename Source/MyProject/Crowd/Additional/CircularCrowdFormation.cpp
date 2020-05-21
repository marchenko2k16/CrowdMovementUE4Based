#include "Crowd/Additional/CircularCrowdFormation.h"

CircularCrowdFormation::CircularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount):
	CrowdFormation(CrowdCenter, CrowdMembersCount)
{
	CircularCrowdFormation::GenerateAgentColumnsLocations(CrowdCenter, CrowdMembersCount);
}

CircularCrowdFormation::~CircularCrowdFormation()
{
}

void CircularCrowdFormation::GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount)
{
}
