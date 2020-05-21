#pragma once

#include "CrowdFormation.h"

class AAgent;

class TriangularCrowdFormation : public CrowdFormation
{
public:
	TriangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount);
	virtual ~TriangularCrowdFormation();
	void GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) override;
};
