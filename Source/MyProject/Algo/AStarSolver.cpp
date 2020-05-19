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
	DrawStartAndGoal(Agent, EndNode, StartNode);

	OpenNodes.Reset();
	ClosedNodes.Reset();
	
	OpenNodes.Emplace(StartNode);

	ESearchResult SearchResult = ESearchResult::Failed;
	GraphNode* CurrentNode = nullptr;

	while (OpenNodes.Num() != 0)
	{
		CurrentNode = GetLowestFCostNode(OpenNodes);
		
		OpenNodes.RemoveSingleSwap(CurrentNode);
		ClosedNodes.Emplace(CurrentNode);

		if (CurrentNode == EndNode)
		{
			SearchResult = ESearchResult::Success;
			break;
		}
		
		const auto Neighbors = Grid->GetNodeNeighbors(CurrentNode);
		for (const auto& CurrentNeighbor : Neighbors)
		{	
			if (!CurrentNeighbor->IsTraversable() || ClosedNodes.Contains(CurrentNeighbor))
			{
				continue;	
			}
			const float_t NewGCost = CurrentNode->GetGCost() + CurrentNeighbor->GetStepCost();
			const float_t NewHCost = Misc::EuclidHeuristics(CurrentNeighbor->GetLocation(), EndNode->GetLocation());
			const float_t NewFCost = NewGCost + NewHCost;
			
			const bool IsNeighborAlreadyOpened = OpenNodes.Contains(CurrentNeighbor);
			
			if (!IsNeighborAlreadyOpened || CurrentNeighbor->GetFCost() < NewFCost)
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
	
	const TArray<GraphNode*> PathPoints = UnpackBuildPath(CurrentNode, Agent);
	Path* GeneratedPath = new Path();

	GeneratedPath->PathGraphNodes = PathPoints;
	Grid->ResetCalculations();
	return TTuple<ESearchResult,Path*>(SearchResult, GeneratedPath);
}

GraphNode* AStarSolver::GetLowestFCostNode(const TArray<GraphNode*>& InOpenNodes) const
{
	const int32 OpenNodesCount = InOpenNodes.Num();
	float MinCost = 0.f;
	int32 MinNodeIndex = 0;

	for (int32 Index = MinNodeIndex + 1; Index < OpenNodesCount; Index++)
	{
		if (InOpenNodes[Index]->GetFCost() < InOpenNodes[MinNodeIndex]->GetFCost())
		{
			MinNodeIndex = Index;
		}
	}
	return InOpenNodes[MinNodeIndex];
}

TArray<GraphNode*> AStarSolver::UnpackBuildPath(GraphNode* LastPathNode, const AAgent* Agent) const
{
	TArray<GraphNode*> ResultPath;
	GraphNode* CurrentNode = LastPathNode;
	while (CurrentNode->GetParentNode())
	{
		ResultPath.EmplaceAt(0, CurrentNode);
		CurrentNode = CurrentNode->GetParentNode();
	}

	DrawBuiltPath(ResultPath, Agent);
	return ResultPath;
}

void AStarSolver::DrawStartAndGoal(const AAgent* Agent, const GraphNode* EndNode, GraphNode* StartNode)
{
	if (ConsoleManager::bVisualDebugGoalPositions)
	{
		DrawDebugLine(Agent->GetWorld(), EndNode->GetLocation() + Constants::ZOffset * 2, EndNode->GetLocation() - Constants::ZOffset, FColor::White, true, 30.f, 0, 20);
		DrawDebugLine(Agent->GetWorld(), StartNode->GetLocation() + Constants::ZOffset * 2, StartNode->GetLocation() - Constants::ZOffset, FColor::White, true, 30.f, 0, 20);
	}
}

void AStarSolver::DrawBuiltPath(TArray<GraphNode*>& ResultPath, const AAgent* Agent) const
{
	if (ConsoleManager::bVisualDebugPath)
	{
		for (const auto& Node : ResultPath)
		{
			DrawDebugLine(Agent->GetWorld(), Node->GetLocation() + Constants::ZOffset, Node->GetLocation() - Constants::ZOffset, FColor::Orange, false, 30.f, 0, 20);
		}
	}

}
