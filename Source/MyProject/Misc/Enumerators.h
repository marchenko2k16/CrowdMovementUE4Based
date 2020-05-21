#pragma once

#include "ObjectMacros.h"

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

UENUM()
enum class EFormationType : uint8
{
	Circular,
	Rectangular,
	Triangular
};