#include "Crowd/Additional/RectangularCrowdFormation.h"

RectangularCrowdFormation::RectangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount):
	CrowdFormation(CrowdCenter, CrowdMembersCount)
{
	RectangularCrowdFormation::GenerateAgentColumnsLocations(CrowdCenter, CrowdMembersCount);
}

RectangularCrowdFormation::~RectangularCrowdFormation()
{}

void RectangularCrowdFormation::GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount)
{}
