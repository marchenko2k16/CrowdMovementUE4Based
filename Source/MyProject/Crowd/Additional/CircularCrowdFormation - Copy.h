#pragma once

#include "CrowdFormation.h"

class AAgent;

class  CircularCrowdFormation : public CrowdFormation
{
	
	CircularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount);
	virtual ~CircularCrowdFormation();
	//TArray<FVector> GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount) override;
};