#include "AStarSolver.h"

#include "Crowd/Agent.h"

#include "GraphNode.h"
#include "Grid.h"

#include "Misc/Misc.h"
#include "Misc/Constants.h"
#include "Misc/ConsoleManager.h"

#include "Algo/MinElement.h"
#include "Path.h"


// ue4
#include "DrawDebugHelpers.h"

TTuple<ESearchResult, Path*> AStarSolver::FindPath(Grid* Grid, GraphNode* StartNode, const GraphNode* EndNode, const AAgent* Agent)
{
	const auto GameWorld = Agent->GetWorld();
	DrawStartAndGoal(EndNode, StartNode, GameWorld);

	OpenNodes.Reset();
	ClosedNodes.Reset();

	OpenNodes.Emplace(StartNode);

	ESearchResult SearchResult = ESearchResult::Failed;
	GraphNode* CurrentNode = nullptr;

	while (OpenNodes.Num()!=0)
	{
		CurrentNode = GetLowestFCostNode(OpenNodes);

		OpenNodes.RemoveSingleSwap(CurrentNode);
		ClosedNodes.Emplace(CurrentNode);

		if (CurrentNode==EndNode)
		{
			SearchResult = ESearchResult::Success;
			break;
		}

		const auto Neighbors = Grid->GetNodeNeighbors(CurrentNode);
		for (const auto& CurrentNeighbor : Neighbors)
		{
			if (!CurrentNeighbor->IsTraversable()||ClosedNodes.Contains(CurrentNeighbor))
			{
				continue;
			}

			//const float DistanceBetweenNodes = Misc::EuclidHeuristics(CurrentNeighbor->GetLocation(), CurrentNode->GetLocation());
			const float DistanceBetweenNodes = Misc::ManhattanHeuristics(CurrentNeighbor->GetLocation(), CurrentNode->GetLocation());
			const float NewGCost = CurrentNode->GetGCost() + CurrentNeighbor->GetStepCost() + DistanceBetweenNodes;
			//const float NewHCost = Misc::EuclidHeuristics(CurrentNeighbor->GetLocation(), EndNode->GetLocation());
			const float NewHCost = Misc::ManhattanHeuristics(CurrentNeighbor->GetLocation(), EndNode->GetLocation());
			const float NewFCost = NewGCost+NewHCost;

			const bool IsNeighborAlreadyOpened = OpenNodes.Contains(CurrentNeighbor);//||ClosedNodes.Contains(CurrentNeighbor);

			if (!IsNeighborAlreadyOpened||NewFCost<CurrentNeighbor->GetFCost())
			{
				CurrentNeighbor->SetParentNode(CurrentNode);
				CurrentNeighbor->SetGCost(NewGCost);
				CurrentNeighbor->SetHCost(NewHCost);
			}

			if (!IsNeighborAlreadyOpened)
			{
				OpenNodes.Emplace(CurrentNeighbor);
			}
		}
	}

	if (ConsoleManager::bVisualDebugOpenClosed)
	{
		DrawOpenedClosedNodes(GameWorld);	
	}

	const TArray<GraphNode*> PathPoints = UnpackBuildPath(CurrentNode, GameWorld);
	Path* GeneratedPath = new Path();

	GeneratedPath->PathGraphNodes = PathPoints;
	Grid->ResetCalculations();
	return TTuple<ESearchResult, Path*>(SearchResult, GeneratedPath);
}

GraphNode* AStarSolver::GetLowestFCostNode(const TArray<GraphNode*>& InOpenNodes) const
{
	const int32 OpenNodesCount = InOpenNodes.Num();
	int32 MinNodeIndex = 0;

	for (int32 Index = MinNodeIndex+1; Index<OpenNodesCount; Index++)
	{
		if (InOpenNodes[Index]->GetFCost()<InOpenNodes[MinNodeIndex]->GetFCost())
		{
			MinNodeIndex = Index;
		}
	}
	return InOpenNodes[MinNodeIndex];
}

TArray<GraphNode*> AStarSolver::UnpackBuildPath(GraphNode* LastPathNode, const UWorld* World) const
{
	TArray<GraphNode*> ResultPath;
	GraphNode* CurrentNode = LastPathNode;
	while (CurrentNode->GetParentNode())
	{
		ResultPath.EmplaceAt(0, CurrentNode);
		CurrentNode = CurrentNode->GetParentNode();
	}
	ResultPath.RemoveSingleSwap(CurrentNode, false);
	DrawBuiltPath(ResultPath, World);
	return ResultPath;
}

void AStarSolver::DrawStartAndGoal(const GraphNode* EndNode, GraphNode* StartNode, const UWorld* World)
{
	if (ConsoleManager::bVisualDebugGoalPositions)
	{
		DrawDebugLine(World, EndNode->GetLocation()+Constants::DebugVectorZOffset*2,
		              EndNode->GetLocation()-Constants::DebugVectorZOffset,
		              FColor::White, true, 30.f, 0, 20);
		DrawDebugLine(World, StartNode->GetLocation()+Constants::DebugVectorZOffset*2,
		              StartNode->GetLocation()-Constants::DebugVectorZOffset,
		              FColor::White, true, 30.f, 0, 20);
	}
}

void AStarSolver::DrawBuiltPath(TArray<GraphNode*>& ResultPath, const UWorld* World) const
{
	if (ConsoleManager::bVisualDebugPath)
	{
		for (const auto& Node : ResultPath)
		{
			DrawDebugLine(World, Node->GetLocation()+Constants::DebugVectorZOffset,
			              Node->GetLocation()-Constants::DebugVectorZOffset,
			              FColor::Orange, false, 30.f, 0, 20);
		}
	}
}

void AStarSolver::DrawOpenedClosedNodes(const UWorld* World) const
{
	for (const auto& Open : OpenNodes)
	{
		DrawDebugLine(World, Open->GetLocation()+Constants::DebugVectorZOffset,
			              Open->GetLocation()-Constants::DebugVectorZOffset,
			              FColor::Green, false, 30.f, 0, 20);
	}

	for (const auto& Closed : ClosedNodes)
	{
		DrawDebugLine(World, Closed->GetLocation()+Constants::DebugVectorZOffset,
			              Closed->GetLocation()-Constants::DebugVectorZOffset,
			              FColor::Red, false, 30.f, 0, 20);
	}
}
