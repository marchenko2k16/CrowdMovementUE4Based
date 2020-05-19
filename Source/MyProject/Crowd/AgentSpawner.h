#pragma once

#include "Agent.h"
#include "AgentSpawner.generated.h"

#include "Misc/Enumerators.h"

class ACrowd;
class ACrowdDirector;

UCLASS()
class AAgentSpawner : public AActor
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAgent> Agent;

protected:
	UPROPERTY(EditAnywhere)
	int32 SpawnCount = 1;
	
	UPROPERTY(EditAnywhere)
	EFormationType FormationType = EFormationType::Rectangular;


	TArray<FVector> GenerateSpawnLocations() const;
public:

	UFUNCTION(CallInEditor)
	void SpawnAgents();

	static ACrowdDirector* SpawnCrowdDirector(UWorld* GameWorld);
};