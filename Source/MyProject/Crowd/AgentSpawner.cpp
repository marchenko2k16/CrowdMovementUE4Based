#include "AgentSpawner.h"

#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"

#include "Misc/NavMeshInfo.h"
#include "Misc/Constants.h"

#include "MyProjectGameMode.h"
#include "Crowd/Crowd.h"

#include "Crowd/CrowdDirector.h"
#include "Additional/RectangularCrowdFormation.h"

void AAgentSpawner::SpawnCrowd()
{
	const FVector SpawnCenter = GetActorLocation()-Constants::DebugVectorZOffset;

	// todo : am : make fabric
	TSharedPtr<CrowdFormation> Formation = nullptr;
	if (FormationType==EFormationType::Rectangular)
	{
		Formation = MakeShared<RectangularCrowdFormation>(SpawnCenter, SpawnCount);
	}

	// todo : am : clean it !!!
	//Formation->AgentPool.Reserve(Formation->Offsets.Num());
	//Formation->AgentPool.SetNumUninitialized(Formation->Offsets.Num());
	for (int32 ColumnIndex = 0; ColumnIndex<Formation->GetOffsetsMutable().Num(); ColumnIndex++)
	{
		//Formation->AgentPool.Reserve(Formation->Offsets[ColumnIndex].Num());
		//Formation->AgentPool.SetNumUninitialized(Formation->Offsets[ColumnIndex].Num());
		Formation->AgentPool.Emplace(TArray<AAgent*>());
		for (const auto& CurrentOffset : Formation->Offsets[ColumnIndex])
		{
			Formation->AgentPool[ColumnIndex].Emplace(SpawnAgent(SpawnCenter+CurrentOffset));
		}
	}

	AMyProjectGameMode::GetCrowd()->SetCrowdFormation(Formation);
	AMyProjectGameMode::GetCrowd()->ReinitializeCrowdDirector();
}

AAgent* AAgentSpawner::SpawnAgent(const FVector& SpawnLocation, const FRotator& SpawnRotation)
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
