#include "Algo/GridGenerator.h"
#include "Algo/Grid.h"
#include "Algo/GraphNode.h"

#include "MyProjectGameMode.h"

#include "Misc/NavMeshInfo.h"
// UE4
#include "NavMeshBoundsVolume.h"
#include "UObjectIterator.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Misc/Constants.h"

void AGridGenerator::BeginPlay()
{
	AMyProjectGameMode::SetGridGenerator(this);
	GenerateGrid();
	RedrawGrid();
}

void AGridGenerator::BeginDestroy()
{
	Super::BeginDestroy();

	if (GlobalGridData)
	{
		delete GlobalGridData;
	}
}

void AGridGenerator::GenerateGrid()
{
	if (GlobalGridData)
	{
		return;
	}
	Grid* GeneratedGrid = new Grid();

	const FVector NavMeshCenter = AMyProjectGameMode::GetNavMeshEssentialsInstance()->GetNavMeshCenter();
	const FVector NavMeshMin = AMyProjectGameMode::GetNavMeshEssentialsInstance()->GetNavMeshMin();
	const FVector NavMeshMax = AMyProjectGameMode::GetNavMeshEssentialsInstance()->GetNavMeshMax();

	const float XMin = NavMeshMin.X;
	const float YMin = NavMeshMin.Y;
	const float XMax = NavMeshMax.X;
	const float YMax = NavMeshMax.Y;

	const auto GetNavMeshPointProjection = [&](const UWorld& World, const FVector& PointToProject)
	{
		FNavLocation PointOnNavMesh = FNavLocation();
		const UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(&World);
		if (!NavSys)
		{
			return PointOnNavMesh.Location;
		}
		NavSys->ProjectPointToNavigation(PointToProject, PointOnNavMesh);
		return PointOnNavMesh.Location;
	};

	UWorld* GameWorld = GetWorld();
	TArray<TArray<GraphNode*>> Nodes;

	int32 GridRow = 0;

	TPair<uint8, uint8> NodeIndex{0, 0};
	for (float CurrentX = XMin; CurrentX<XMax; CurrentX += Constants::GridStep,GridRow++)
	{
		Nodes.Emplace(TArray<GraphNode*>());
		for (float CurrentY = YMin; CurrentY<YMax; CurrentY += Constants::GridStep)
		{
			GraphNode* Node = new GraphNode();
			//Node->SetGridPtr(GeneratedGrid);
			Node->SetStepCost(Constants::BaseStepCost);
			Node->SetIndex(NodeIndex);

			FVector CurrentPresumableGraphPoint{CurrentX+Constants::HalfGridStep, CurrentY+Constants::HalfGridStep, NavMeshCenter.Z};
			const FVector GraphNodeLocation = GetNavMeshPointProjection(*GameWorld, CurrentPresumableGraphPoint);

			if (GraphNodeLocation==FVector::ZeroVector)
			{
				Node->SetLocation(CurrentPresumableGraphPoint);
				Node->SetTraversability(EGraphNodeTraversability::NonTraversable);
			}
			else
			{
				Node->SetLocation(GraphNodeLocation);
				Node->SetTraversability(EGraphNodeTraversability::Traversable);
			}
			Nodes[GridRow].Emplace(Node);
			NodeIndex.Value++;
		}
		NodeIndex.Value = 0;
		NodeIndex.Key++;
	}
	GeneratedGrid->SetGraph(Nodes);
	GeneratedGrid->SetGridCenter(NavMeshCenter);

	GeneratedGrid->ModifyBaseWeights();

	GlobalGridData = GeneratedGrid;
}

void AGridGenerator::RedrawGrid()
{
	UWorld* GameWorld = GetWorld();

	if (!GameWorld)
	{
		return;
	}

	if (!GlobalGridData)
	{
		return;
	}

	ModifyWalkableAreaOnRuntime(GlobalGridData);

	for (const auto NodeRow : GlobalGridData->GetNodePoolConst())
	{
		for (const auto Node : NodeRow)
		{
			if (Node->IsTraversable())
			{
				DrawDebugLine(GameWorld, Node->GetLocation()+Constants::DebugVectorZOffset,
				              Node->GetLocation()-Constants::DebugVectorZOffset, FColor::Green, false, 3.f, 0, 20);
			}
			else
			{
				DrawDebugLine(GameWorld, Node->GetLocation()+Constants::DebugVectorZOffset,
				              Node->GetLocation()-Constants::DebugVectorZOffset, FColor::Red, false, 3.f, 0, 20);
			}
		}
	}
}

void AGridGenerator::ModifyWalkableAreaOnRuntime(Grid* GridData)
{
	const auto GameWorld = GetWorld();
	if (!GameWorld)
	{
		return;
	}

	if (!GridData)
	{
		return;
	}

	const FVector Offset{Constants::HalfGridStep, Constants::HalfGridStep, 0};
	for (const auto& Row : GridData->GetNodePoolMutable())
	{
		for (const auto& Element : Row)
		{
			const FVector ElementLocation = Element->GetLocation();
			const FVector LeftBound = ElementLocation-Offset;
			const FVector RightBound = ElementLocation-Offset;

			//unused in our algo, optional param
			static FVector HitLocation;

			if (UNavigationSystemV1::NavigationRaycast(GameWorld, LeftBound, RightBound, HitLocation))
			{
				Element->SetTraversability(EGraphNodeTraversability::NonTraversable);
			}
			else
			{
				Element->SetTraversability(EGraphNodeTraversability::Traversable);
			}
		}
	}
}

GraphNode* AGridGenerator::GetGraphNodeByLocation(const FVector& RealWordLocation) const
{
	const int32 GridHeight = GlobalGridData->GetNodePoolConst().Num();
	const int32 GridWidth = GlobalGridData->GetNodePoolConst().Last().Num();

	const int32 HalfGridHeight = GridHeight/2;
	const int32 HalfGridWidth = GridWidth/2;

	const FVector GridCellRowColumnValues = (RealWordLocation-GlobalGridData->GetGridCenter())/Constants::GridStep;

	const int8 XAdditionalOffset = GridCellRowColumnValues.X>0 ? 0 : -1;
	const int8 YAdditionalOffset = GridCellRowColumnValues.Y>0 ? 0 : -1;

	const int32 RealToRowX = GridCellRowColumnValues.X+HalfGridHeight+XAdditionalOffset;
	const int32 RealToRowY = GridCellRowColumnValues.Y+HalfGridWidth+YAdditionalOffset;

	if (RealToRowX<0||RealToRowX>=GridHeight||RealToRowY<0||RealToRowY>=GridWidth)
	{
		return nullptr;
	}
	return GlobalGridData->GetGraphNodeMutable(RealToRowX, RealToRowY);
}

Grid* AGridGenerator::GetGlobalGridData() const
{
	return GlobalGridData;
}
