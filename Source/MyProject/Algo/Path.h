#pragma once

// UE4
#include "Array.h"

class GraphNode;

struct Path
{
	TArray<GraphNode*> PathGraphNodes;
	class AAgent* PathOwner = nullptr;
	float PathBuiltTimestamp = 0.f;
	
	int32 CurrentGraphNodeIndex = -1;
	bool IncrementToNextGraphNode();

	GraphNode* GetNextGraphNode();
	GraphNode* GetNextGraphNodeSafe();
	void OnMovementInterrupted();
};
