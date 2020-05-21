#include "Crowd/Additional/RectangularCrowdFormation.h"

RectangularCrowdFormation::RectangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount):
	CrowdFormation(CrowdCenter, CrowdMembersCount)
{
	RectangularCrowdFormation::GenerateAgentColumnsLocations(CrowdCenter, CrowdMembersCount);
}

RectangularCrowdFormation::~RectangularCrowdFormation()
{}

void RectangularCrowdFormation::GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount)
{
	// todo : am : fix hardcoded
	Offsets.Emplace(TArray<FVector>());
	Offsets[0].Emplace(CrowdCenter - FVector{0,0,200});

	const float Offset = 100.f;
	FVector::ForwardVector;
	FVector::BackwardVector;
	
	FVector::RightVector;
	FVector::LeftVector;

	const FVector XOffset = {0,0,100};
}
