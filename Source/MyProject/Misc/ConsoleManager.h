#pragma once

// UE4 includes
#include "GameFramework/Info.h"

class ConsoleManager
{

public:
	static bool bVisualDebugPath;
	static bool bVisualDebugGoalPositions;
	static bool bVisualDebugOpenClosed;
	
	static void ToggleDebugPath();
	static void ToggleDebugGoalPositions();
	static void ToggleDebugOpenClosed();
};