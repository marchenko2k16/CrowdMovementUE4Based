#include "AgentSpawner.h"

#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"

#include "Misc/NavMeshInfo.h"
#include "MyProjectGameMode.h"

#include "Crowd/Crowd.h"
#include "Crowd/CrowdDirector.h"


//TArray<AAgent*> AAgentSpawner::SpawnedAgents;
//ACrowd* AAgentSpawner::StaticCrowdPointer = nullptr;

TArray<FVector> AAgentSpawner::GenerateSpawnLocations() const
{
	constexpr float StepBetweenAgents = 86.f;
	

	TArray<FVector> AgentsSpawnLocations;

	const auto CurrentProjectGameMode = Cast<AMyProjectGameMode>(UGameplayStatics::GetGameMode(this));

	//const FVector Center = AMyProjectGameMode::GetNavMeshEssentialsInstance()->GetNavMeshCenter() + FVector{0.f, 0.f, 700.f};
	//const FVector Min = AMyProjectGameMode::GetNavMeshEssentialsInstance()->GetNavMeshMin();
	//const FVector Max = AMyProjectGameMode::GetNavMeshEssentialsInstance()->GetNavMeshMax();

	//const float XLength = FMath::Abs(Max.X - Min.X);
	//const float YLength = FMath::Abs(Max.Y - Min.Y);

	//const int32 AgentLimitPerLine = XLength / StepBetweenAgents - 2;
	//const int32 AgentLimitPerLine = 30;

	//float XOffset = 0.f;
	//float YOffset = 0.f;
	//const FVector StartSpawnPoint = Center - FVector{0.f,YLength / 2 ,0.f} + FVector{0.f,StepBetweenAgents/2 ,0.f};

	const FVector SpawnCenter = GetActorLocation();

	for (int32 SpawnedAgentCount = 1; SpawnedAgentCount <= SpawnCount; SpawnedAgentCount++)
	{
		const FVector XOffsetVector{XOffset, 0.f,0.f};
		const FVector YOffsetVector{0.f, YOffset,0.f};
		
		FVector NewLocation = FVector::ZeroVector;
		if (SpawnedAgentCount % 2 == 0)
		{
			NewLocation = StartSpawnPoint + YOffsetVector + XOffsetVector;	
		}
		else
		{
			NewLocation = StartSpawnPoint + YOffsetVector - XOffsetVector;	
		}
		
		AgentsSpawnLocations.Emplace(NewLocation);


		if (SpawnedAgentCount % 2)
		{
			XOffset += StepBetweenAgents;
		}
		
		if (SpawnedAgentCount % AgentLimitPerLine == 0)
		{
			YOffset += StepBetweenAgents;
			XOffset = 0.f;
		}
	}
	return AgentsSpawnLocations;
}

void AAgentSpawner::SpawnAgents()
{
	if (!Agent)
	{
		ensure("No Agent Set");
		return;
	}
	UWorld* GameWorld = GetWorld();
	if (!GameWorld)
	{
		ensure("No GameWorld");
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.bDeferConstruction = true;
	const FRotator SpawnRotation = FRotator::ZeroRotator;	

	TArray<FVector> SpawnLocations = GenerateSpawnLocations();

	TArray<AAgent*> SpawnedAgents;

	for (const auto& SpawnLocation : SpawnLocations )
	{
		const FTransform SpawnTransform{SpawnRotation, SpawnLocation};
		AAgent* SpawnedAgent = Cast<AAgent>(GameWorld->SpawnActor<AAgent>(Agent, SpawnTransform, SpawnParameters));
		if (!SpawnedAgent)
		{
			continue;
		}
		SpawnedAgent->Modify();
		SpawnedAgent->AutoPossessAI = EAutoPossessAI::Spawned;
		
		UGameplayStatics::FinishSpawningActor(SpawnedAgent, SpawnTransform);
		
		SpawnedAgents.Emplace(SpawnedAgent);
		SpawnedAgent->SetAgentIndex(SpawnedAgents.Num());
	}

	AMyProjectGameMode::GetCrowd()->SetAgentPool(SpawnedAgents);
	AMyProjectGameMode::GetCrowd()->ReinitCrowdDirector();
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
	ACrowdDirector* SpawnedCrowdDirector = Cast<ACrowdDirector>(GameWorld->SpawnActor<ACrowdDirector>(ACrowdDirector::StaticClass(), SpawnTransform, SpawnParameters));
	if (!SpawnedCrowdDirector)
	{
		return nullptr;
	}
	SpawnedCrowdDirector->Modify();
	
	UGameplayStatics::FinishSpawningActor(SpawnedCrowdDirector, SpawnTransform);

	return SpawnedCrowdDirector;
}
