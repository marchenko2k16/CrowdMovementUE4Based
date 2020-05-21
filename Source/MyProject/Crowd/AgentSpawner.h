#pragma once

#include "Agent.h"

#include "Misc/Enumerators.h"

#include "AgentSpawner.generated.h"

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
	//UPROPERTY(EditAnywhere)
	//int32 SpawnCount = 1;
	
	UPROPERTY(EditAnywhere)
	EFormationType FormationType = EFormationType::Rectangular;

	int32 SpawnedCrowdCount = 0;
	int32 SpawnAgentCount = 0;
	
public:

	UFUNCTION(CallInEditor)
	void SpawnCrowd();

	AAgent* SpawnAgents(const FVector& SpawnLocation = FVector::ZeroVector, const FRotator& SpawnRotation = FRotator::ZeroRotator);

	static ACrowdDirector* SpawnCrowdDirector(UWorld* GameWorld);
};