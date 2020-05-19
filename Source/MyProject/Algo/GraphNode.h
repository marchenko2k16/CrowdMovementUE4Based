#pragma once

#include "Misc/Enumerators.h"

// UE4
#include "CoreMinimal.h"

class Grid;

class GraphNode
{
private:

	FVector Location = FVector::ZeroVector;

	Grid* NodeGrid = nullptr;
	GraphNode* ParentNode = nullptr;

	float GCost = 0.f;
	float HCost = 0.f;
	float NodeStepCost = 0.f;
	EGraphNodeTraversability Traversability = EGraphNodeTraversability::NonTraversable;

	TPair<int32, int32> Index;

public:
	GraphNode() = default;
	~GraphNode() = default;

	void SetGridPtr(Grid* InGrid);

	void SetGCost(float_t InCost);
	void SetHCost(float_t InCost);
	void SetStepCost(float_t InCost);
	void SetLocation(const FVector& InLocation);

	void SetParentNode(GraphNode* InParent);
	void SetTraversability(EGraphNodeTraversability InTraversability);

	void SetIndex(TPair<int32, int32> InIndex);

	float_t GetGCost() const;
	float_t GetHCost() const;
	float_t GetFCost() const;
	float_t GetStepCost() const;

	GraphNode* GetParentNode() const;

	FVector GetLocation() const;
	const TPair<int32, int32>& GetIndex() const;

	EGraphNodeTraversability GetTraversability() const;

	bool IsTraversable() const;
};
