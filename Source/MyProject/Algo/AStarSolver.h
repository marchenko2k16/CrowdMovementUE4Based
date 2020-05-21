#pragma once

#include "CoreMinimal.h"

#include "Misc/Enumerators.h"

class AAgent;
class Grid;
class GraphNode;

struct Path;

// todo : am : make pre allocation of arrays
// todo : am : try to find way to avoid graph fields reset to defaults and make some lightweight structure to be contained in OpenClosed/ClosedNodes while building path

class AStarSolver
{
private:
	TArray<GraphNode*> OpenNodes;
	TArray<GraphNode*> ClosedNodes;

	GraphNode* GetLowestFCostNode(const TArray<GraphNode*>& InOpenNodes) const;
	TArray<GraphNode*> UnpackBuildPath(GraphNode* LastPathNode, const AAgent* Agent) const;
	void DrawStartAndGoal(const AAgent* Agent, const GraphNode* EndNode, GraphNode* StartNode);
	void DrawBuiltPath(TArray<GraphNode*>& ResultPath, const AAgent* Agent) const;

public:
	TTuple<ESearchResult, Path*> FindPath(Grid* Grid, GraphNode* StartNode, const GraphNode* EndNode, const AAgent* Agent);
};
