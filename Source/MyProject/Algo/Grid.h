#pragma once

#include "Graph.h"

// UE4
#include "CoreMinimal.h"

class GraphNode;

class Grid : public Graph
{
public:

	Grid() = default;
	virtual ~Grid();
	//Grid(const TArray<TArray<GraphNode*>>& NodePool);
	
	const TArray<TArray<GraphNode*>>& GetNodePoolConst() const override;
	TArray<TArray<GraphNode*>>& GetNodePoolMutable() override;
	
	void SetGraph(TArray<TArray<GraphNode*>>& NodePool) override;

	GraphNode* GetGraphNodeMutable(int32 Row, int32 Column) override;
	const GraphNode* GetGraphNodeConst(int32 Row, int32 Column) const override;

	void SetGridCenter(const FVector& InGridCenter) override;
	FVector GetGridCenter() const override;

	TArray<GraphNode*> GetNodeNeighbors(const GraphNode* InNode) override;

	void ResetCalculations();
};
