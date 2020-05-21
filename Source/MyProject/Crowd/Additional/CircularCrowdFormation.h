#pragma once

#include "CrowdFormation.h"

class AAgent;

class CircularCrowdFormation : public CrowdFormation
{
public:
	CircularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount);
	virtual ~CircularCrowdFormation();
	void GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) override;
};
