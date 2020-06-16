#pragma once

#include "Misc/Enumerators.h"

// UE4
#include "CoreMinimal.h"

class Grid;

class GraphNode
{
private:

	FVector Location = FVector::ZeroVector;
	GraphNode* ParentNode = nullptr;

	float GCost = 0.f;
	float HCost = 0.f;
	float NodeStepCost = 0.f;

	TPair<uint8, uint8> Index;
	EGraphNodeTraversability Traversability = EGraphNodeTraversability::NonTraversable;

public:
	GraphNode() = default;
	~GraphNode() = default;

	//void SetGridPtr(Grid* InGrid);

	void SetGCost(float_t InCost);
	void SetHCost(float_t InCost);
	void SetStepCost(float_t InCost);
	void SetLocation(const FVector& InLocation);

	void SetParentNode(GraphNode* InParent);
	void SetTraversability(EGraphNodeTraversability InTraversability);

	void SetIndex(TPair<uint8, uint8> InIndex);

	float_t GetGCost() const;
	float_t GetHCost() const;
	float_t GetFCost() const;
	float_t GetStepCost() const;

	GraphNode* GetParentNode() const;

	FVector GetLocation() const;
	const TPair<uint8, uint8>& GetIndex() const;

	EGraphNodeTraversability GetTraversability() const;

	bool IsTraversable() const;
};
