#pragma once

#include "CoreMinimal.h"

//#include "Private/PostProcess/PostProcessGBufferHints.h"

enum class ESearchResult : uint8
{
	Success,
	Failed,
	GoalUnreachable
};

enum class EGraphNodeTraversability : uint8
{
	Traversable,
	NonTraversable,
	Traversed
};

enum class EHeuristics: uint8
{
	Euler,
	Manhattan
};

enum class EMovementRequestType : uint8
{
	UE4,
	AStarDefault,
	AStarDelay,
	BFSAStar
};

enum class EFormationType : uint8
{
	Circular,
	Rectangular,
	Triangular
};