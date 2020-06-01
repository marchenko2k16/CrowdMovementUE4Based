#include "Misc/ConsoleManager.h"

bool ConsoleManager::bVisualDebugPath = false;
bool ConsoleManager::bVisualDebugGoalPositions = false;
bool ConsoleManager::bVisualDebugOpenClosed = false;

void ConsoleManager::ToggleDebugPath()
{
	bVisualDebugPath = !bVisualDebugPath;
}

void ConsoleManager::ToggleDebugGoalPositions()
{
	bVisualDebugGoalPositions = !bVisualDebugGoalPositions;
}

void ConsoleManager::ToggleDebugOpenClosed()
{
	bVisualDebugOpenClosed = !bVisualDebugOpenClosed;
}
