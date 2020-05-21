#include "Crowd/Additional/TriangularCrowdFormation.h"

TriangularCrowdFormation::TriangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount):
	CrowdFormation(CrowdCenter, CrowdMembersCount)
{
	TriangularCrowdFormation::GenerateAgentColumnsLocations(CrowdCenter, CrowdMembersCount);
}

TriangularCrowdFormation::~TriangularCrowdFormation()
{}

void TriangularCrowdFormation::GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount)
{}
