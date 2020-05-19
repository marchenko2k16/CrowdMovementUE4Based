#pragma once

#include "CrowdFormation.h"

class AAgent;

class  RectangularCrowdFormation : public CrowdFormation
{
	RectangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount);
	virtual ~RectangularCrowdFormation();
	//TArray<FVector> GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) override;
};