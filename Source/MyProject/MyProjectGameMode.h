// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "MyProjectGameMode.generated.h"

class Crowd;
class NavMeshEssentials;
class AGridGenerator;

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	static NavMeshEssentials* NavMeshEssentialsInstance;
	static Crowd* TesMapCrowd;
	static AGridGenerator* GridGenerator;

	static UWorld* GameWorld;

protected:
	void BeginPlay() override;

public:
	AMyProjectGameMode();
	void BeginDestroy() override;
	
	static NavMeshEssentials* GetNavMeshEssentialsInstance();
	static Crowd* GetCrowd();
	static UWorld* GetGameWorld();
	
	static void SetGridGenerator(AGridGenerator* InGridGenerator);
	static AGridGenerator* GetGridGenerator();
};