#pragma once

#include "CrowdFormation.h"

class AAgent;

class TriangularCrowdFormation : public CrowdFormation
{
	TriangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount);
	virtual ~TriangularCrowdFormation();
	void GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) override;
};
