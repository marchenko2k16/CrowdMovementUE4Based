#pragma once

#include "CoreMinimal.h"
//#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Actor.h"

#include "GridGenerator.generated.h"

class Grid;
class GraphNode;
UCLASS()
class AGridGenerator : public AActor
{
	GENERATED_BODY()

private:
	Grid* GlobalGridData = nullptr;

protected:
	void BeginPlay() override;

public:
	void BeginDestroy() override;

	UFUNCTION(CallInEditor)
	void GenerateGrid();

	UFUNCTION(CallInEditor)
	void RedrawGrid();

	void ModifyWalkableAreaOnRuntime(Grid* GridData);
	GraphNode* GetGraphNodeByLocation(const FVector& RealWordLocation) const;

	Grid* GetGlobalGridData() const;
};