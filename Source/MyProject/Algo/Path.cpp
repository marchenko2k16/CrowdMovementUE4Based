#include "Path.h"
#include "Algo/GraphNode.h"

bool Path::IncrementToNextGraphNode()
{
	CurrentGraphNodeIndex++;
	return PathGraphNodes.IsValidIndex(CurrentGraphNodeIndex);
}

GraphNode* Path::GetNextGraphNode()
{
	if (!IncrementToNextGraphNode())
	{
		return nullptr;		
	}
	return PathGraphNodes[CurrentGraphNodeIndex];
}

GraphNode* Path::GetNextGraphNodeSafe()
{
	if (PathGraphNodes.IsValidIndex(CurrentGraphNodeIndex))
	{
		return PathGraphNodes[CurrentGraphNodeIndex];
	}
	return nullptr;
}

void Path::OnMovementInterrupted()
{
	CurrentGraphNodeIndex--;
}
