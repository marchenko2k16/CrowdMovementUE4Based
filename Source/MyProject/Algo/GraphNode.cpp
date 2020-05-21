#include "GraphNode.h"
#include "Grid.h"

void GraphNode::SetGridPtr(Grid* InGrid)
{
	NodeGrid = InGrid;
}

void GraphNode::SetGCost(float_t InCost)
{
	GCost = InCost;
}

void GraphNode::SetHCost(float_t InCost)
{
	HCost = InCost;
}

void GraphNode::SetStepCost(float_t InCost)
{
	NodeStepCost = InCost;
}

void GraphNode::SetLocation(const FVector& InLocation)
{
	Location = InLocation;
}

void GraphNode::SetParentNode(GraphNode* InParent)
{
	ParentNode = InParent;
}

void GraphNode::SetTraversability(EGraphNodeTraversability InTraversability)
{
	Traversability = InTraversability;
}

void GraphNode::SetIndex(TPair<int32, int32> InIndex)
{
	Index = InIndex;
}

float_t GraphNode::GetGCost() const
{
	return GCost;
}

float_t GraphNode::GetHCost() const
{
	return HCost;
}

float_t GraphNode::GetFCost() const
{
	return GCost+HCost;
}

float_t GraphNode::GetStepCost() const
{
	return NodeStepCost;
}

GraphNode* GraphNode::GetParentNode() const
{
	return ParentNode;
}

FVector GraphNode::GetLocation() const
{
	return Location;
}

const TPair<int32, int32>& GraphNode::GetIndex() const
{
	return Index;
}

EGraphNodeTraversability GraphNode::GetTraversability() const
{
	return Traversability;
}

bool GraphNode::IsTraversable() const
{
	return Traversability==EGraphNodeTraversability::Traversable;
}
