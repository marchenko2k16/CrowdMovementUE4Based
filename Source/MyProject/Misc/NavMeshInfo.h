#pragma once

#include "CoreMinimal.h"
#include "NavMeshBoundsVolume.h"


class NavMeshEssentials
{

private:
	//static NavMeshEssentials* NavMeshEssentialsInstance;

	
	ANavMeshBoundsVolume* NavMesh = nullptr;

	FVector NavMeshMin = FVector::ZeroVector;
	FVector NavMeshMax = FVector::ZeroVector;
	FVector NavMeshCenter = FVector::ZeroVector;
protected:
	
public:
	NavMeshEssentials()
	{
		CalculateCurrentMapNavMeshEssentials();
	}
	
	NavMeshEssentials(const NavMeshEssentials&)
	{};  
	

	FVector GetNavMeshMin() const;
	FVector GetNavMeshMax() const;
	FVector GetNavMeshCenter() const;

	ANavMeshBoundsVolume* GetNavMesh();
	

	void CalculateCurrentMapNavMeshEssentials();
};
