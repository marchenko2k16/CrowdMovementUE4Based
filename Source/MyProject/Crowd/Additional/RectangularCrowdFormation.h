#pragma once

#include "CrowdFormation.h"

class AAgent;

class  RectangularCrowdFormation : public CrowdFormation
{
	// todo : am : finilize
	RectangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount = 100);
	virtual ~RectangularCrowdFormation();
	void GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) override;
};