#include "Grid.h"
#include "GraphNode.h"
#include "Misc/Constants.h"

Grid::~Grid()
{
	for (auto& NodeRow : NodePool)
	{
		for (auto& Node : NodeRow)
		{
			delete Node;
		}
		NodeRow.Reset();
	}
	NodePool.Reset();
}

const TArray<TArray<GraphNode*>>& Grid::GetNodePoolConst() const
{
	return NodePool;
}

TArray<TArray<GraphNode*>>& Grid::GetNodePoolMutable()
{
	return NodePool;
}

void Grid::SetGraph(TArray<TArray<GraphNode*>>& InNodePool)
{
	NodePool = InNodePool;
}

GraphNode* Grid::GetGraphNodeMutable(int32 Row, int32 Column)
{
	if (!NodePool.IsValidIndex(Row))
	{
		return nullptr;
	}
	if (!NodePool.Last().IsValidIndex(Column))
	{
		return nullptr;
	}

	return NodePool[Row][Column];
}

const GraphNode* Grid::GetGraphNodeConst(int32 Row, int32 Column) const
{
	if (!NodePool.IsValidIndex(Row))
	{
		return nullptr;
	}
	if (!NodePool.IsValidIndex(Column))
	{
		return nullptr;
	}

	return NodePool[Row][Column];
}

void Grid::SetGridCenter(const FVector& InGridCenter)
{
	GridCenter = InGridCenter;
}

FVector Grid::GetGridCenter() const
{
	return GridCenter;
}

TArray<GraphNode*> Grid::GetNodeNeighbors(const GraphNode* InNode)
{
	TArray<GraphNode*> Neighbors;

	const auto NodeIndex = InNode->GetIndex();
	for (int Row = NodeIndex.Key-1; Row<=NodeIndex.Key+1; Row++)
	{
		for (int Column = NodeIndex.Value-1; Column<=NodeIndex.Value+1; Column++)
		{
			if (Row==NodeIndex.Key&&Column==NodeIndex.Value)
			{
				continue;
			}
			const auto Node = GetGraphNodeMutable(Row, Column);
			if (!Node)
			{
				continue;
			}
			Neighbors.Emplace(Node);
		}
	}
	return Neighbors;
}

void Grid::ModifyBaseWeights()
{
	for (auto& NodeRow : NodePool)
	{
		for (auto& Node : NodeRow)
		{
			float AdditionalBaseWeight = 0.f;
			for (const auto Neighbor : GetNodeNeighbors(Node))
			{
				if (!Neighbor->IsTraversable())
				{
					AdditionalBaseWeight += Constants::NonTraversableNeighborIncreasingCost;
				}
			}
			const float NewStepCost = Node->GetStepCost()+AdditionalBaseWeight;
			Node->SetStepCost(NewStepCost);
		}
	}
}

// todo : am : get rid of this tricky smelly code :(
void Grid::ResetCalculations()
{
	for (auto& NodeRow : NodePool)
	{
		for (auto& Node : NodeRow)
		{
			Node->SetParentNode(nullptr);
			Node->SetHCost(0.f);
			Node->SetGCost(0.f);
		}
	}
}
