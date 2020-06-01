// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Misc/NavMeshInfo.h"
#include "Crowd/Crowd.h"
#include "Algo/GridGenerator.h"
#include "Kismet/GameplayStatics.h"

NavMeshEssentials* AMyProjectGameMode::NavMeshEssentialsInstance = nullptr;
Crowd* AMyProjectGameMode::TesMapCrowd = nullptr;
AGridGenerator* AMyProjectGameMode::GridGenerator = nullptr;
UWorld* AMyProjectGameMode::GameWorld = nullptr;

void AMyProjectGameMode::BeginPlay()
{
	GameWorld = GetWorld();
	static ACharacter* PlayerCharacter;
}

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class!=NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyProjectGameMode::BeginDestroy()
{
	Super::BeginDestroy();

	// todo : am : extract to separate functions
	if (NavMeshEssentialsInstance)
	{
		delete NavMeshEssentialsInstance;
		NavMeshEssentialsInstance = nullptr;
	}

	if (TesMapCrowd)
	{
		delete TesMapCrowd;
		TesMapCrowd = nullptr;
	}

	if (GridGenerator)
	{
		GridGenerator = nullptr;
	}
	if (GameWorld)
	{
		GameWorld = nullptr;
	}
}

NavMeshEssentials* AMyProjectGameMode::GetNavMeshEssentialsInstance()
{
	if (!NavMeshEssentialsInstance)
	{
		NavMeshEssentialsInstance = new NavMeshEssentials();
	}
	return NavMeshEssentialsInstance;
}

Crowd* AMyProjectGameMode::GetCrowd()
{
	if (!TesMapCrowd)
	{
		TesMapCrowd = new Crowd();
	}

	return TesMapCrowd;
}

UWorld* AMyProjectGameMode::GetGameWorld()
{
	return GameWorld;
}

void AMyProjectGameMode::SetGridGenerator(AGridGenerator* InGridGenerator)
{
	GridGenerator = InGridGenerator;
}

AGridGenerator* AMyProjectGameMode::GetGridGenerator()
{
	return GridGenerator;
}