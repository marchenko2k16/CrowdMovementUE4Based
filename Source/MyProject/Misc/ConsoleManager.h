#pragma once

// UE4 includes
#include "GameFramework/Info.h"

class ConsoleManager
{

public:
	static bool bVisualDebugPath;
	static bool bVisualDebugGoalPositions;
	
	static void ToggleDebugPath();
	static void ToggleDebugGoalPositions();
};