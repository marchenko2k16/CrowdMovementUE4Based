#include "Misc/ConsoleManager.h"

bool ConsoleManager::bVisualDebugPath = false;
bool ConsoleManager::bVisualDebugGoalPositions = false;

void ConsoleManager::ToggleDebugPath()
{
	bVisualDebugPath = !bVisualDebugPath;
}

void ConsoleManager::ToggleDebugGoalPositions()
{
	bVisualDebugGoalPositions = !bVisualDebugGoalPositions;
}
