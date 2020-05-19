#include "Misc/NavMeshInfo.h"

// UE4
#include "NavMeshBoundsVolume.h"
#include "UObjectIterator.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"

//NavMeshEssentials* NavMeshEssentials::NavMeshEssentialsInstance;

FVector NavMeshEssentials::GetNavMeshMin() const
{
	return NavMeshMin;
}

FVector NavMeshEssentials::GetNavMeshMax() const
{
	return NavMeshMax;
}

FVector NavMeshEssentials::GetNavMeshCenter() const
{
	return NavMeshCenter;
}

ANavMeshBoundsVolume* NavMeshEssentials::GetNavMesh()
{
	return nullptr;
}

void NavMeshEssentials::CalculateCurrentMapNavMeshEssentials()
{
	ANavMeshBoundsVolume* NavMesh = nullptr;
	for (TObjectIterator<ANavMeshBoundsVolume> ObjectIterator; ObjectIterator; ++ObjectIterator)
	{
		NavMesh = *ObjectIterator;
	}

	if (!NavMesh)
	{
		return;
	}

	const FBoxSphereBounds Bounds = NavMesh->GetBounds();
	NavMeshMin = Bounds.GetBox().Min;
	NavMeshMax = Bounds.GetBox().Max;
	NavMeshCenter = Bounds.GetBox().GetCenter();	
}