#include "AgentSpawner.h"

#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"

#include "Misc/NavMeshInfo.h"
#include "MyProjectGameMode.h"

#include "Crowd/Crowd.h"
#include "Crowd/CrowdDirector.h"
#include "Additional/RectangularCrowdFormation.h"

void AAgentSpawner::SpawnCrowd()
{
	const auto CurrentProjectGameMode = Cast<AMyProjectGameMode>(UGameplayStatics::GetGameMode(this));

	const FVector SpawnCenter = GetActorLocation();

	// todo : am : make fabric
	CrowdFormation* Formation = nullptr;
	if (FormationType==EFormationType::Rectangular)
	{
		Formation = new RectangularCrowdFormation(SpawnCenter);
	}

	Formation->AgentPool.Reserve(Formation->Offsets.Num());

	for (int32 ColumnIndex = 0; ColumnIndex<Formation->GetOffsetsMutable().Num(); ColumnIndex++)
	{
		Formation->AgentPool.Reserve(Formation->Offsets[ColumnIndex].Num());

		for (const auto& CurrentOffset : Formation->Offsets[ColumnIndex])
		{
			Formation->AgentPool[ColumnIndex].Emplace(SpawnAgents(SpawnCenter+CurrentOffset));
		}
	}

	AMyProjectGameMode::GetCrowd()->SetCrowdFormation(Formation);
	AMyProjectGameMode::GetCrowd()->ReinitCrowdDirector();
}

AAgent* AAgentSpawner::SpawnAgents(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	if (!Agent)
	{
		ensure("No Agent Set");
		return nullptr;
	}
	UWorld* GameWorld = GetWorld();
	if (!GameWorld)
	{
		ensure("No GameWorld");
		return nullptr;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bDeferConstruction = true;

	const FTransform SpawnTransform{SpawnRotation, SpawnLocation};
	AAgent* SpawnedAgent = Cast<AAgent>(GameWorld->SpawnActor<AAgent>(Agent, SpawnTransform, SpawnParameters));
	if (!SpawnedAgent)
	{
		return nullptr;
	}
	SpawnedAgent->Modify();
	SpawnedAgent->AutoPossessAI = EAutoPossessAI::Spawned;

	UGameplayStatics::FinishSpawningActor(SpawnedAgent, SpawnTransform);

	SpawnedAgent->SetAgentIndex(++SpawnAgentCount);
	return SpawnedAgent;
}

ACrowdDirector* AAgentSpawner::SpawnCrowdDirector(UWorld* GameWorld)
{
	if (!GameWorld)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bDeferConstruction = true;

	const FTransform SpawnTransform{FRotator::ZeroRotator, FVector::ZeroVector};
	ACrowdDirector* SpawnedCrowdDirector = Cast<ACrowdDirector>(
		GameWorld->SpawnActor<ACrowdDirector>(ACrowdDirector::StaticClass(), SpawnTransform, SpawnParameters));
	if (!SpawnedCrowdDirector)
	{
		return nullptr;
	}
	SpawnedCrowdDirector->Modify();

	UGameplayStatics::FinishSpawningActor(SpawnedCrowdDirector, SpawnTransform);

	return SpawnedCrowdDirector;
}
