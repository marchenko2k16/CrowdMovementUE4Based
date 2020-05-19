#pragma once

#include "CoreMinimal.h"

class GraphNode;

class Graph
{
protected:

	TArray<TArray<GraphNode*>> NodePool;
	FVector GridCenter = FVector::ZeroVector;

public:

	Graph() = default;
	virtual ~Graph() = default;
	
	//Graph(const TArray<TArray<GraphNode*>>& InNodePool) : NodePool(InNodePool){}

	virtual const TArray<TArray<GraphNode*>>& GetNodePoolConst() const = 0;
	virtual TArray<TArray<GraphNode*>>& GetNodePoolMutable() = 0;

	virtual void SetGraph(TArray<TArray<GraphNode*>>& NodePool) = 0;

	virtual GraphNode* GetGraphNodeMutable(int32 Row, int32 Column) = 0;
	virtual const GraphNode* GetGraphNodeConst(int32 Row, int32 Column) const = 0;

	virtual void SetGridCenter(const FVector& GridCenter) = 0;
	virtual FVector GetGridCenter() const = 0;

	virtual TArray<GraphNode*> GetNodeNeighbors(const GraphNode* InNode) = 0;
};
