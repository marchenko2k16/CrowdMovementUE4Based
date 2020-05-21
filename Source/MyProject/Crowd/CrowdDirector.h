#pragma once

#include "GameFramework/Actor.h"

#include "Crowd/Additional/CrowdMovementRequest.h"

#include "CrowdDirector.generated.h"


class AAgent;
class Crowd;

struct Path;


//class CrowdMovementRequest;
UCLASS()
	class ACrowdDirector : public AActor
{
	GENERATED_BODY()

private:
	TMap<int32, Path*> AgentPaths;
	Crowd* DirectedCrowd = nullptr;
	
	// todo : am : try to find way to make shared
	//TUniquePtr<CrowdMovementRequest> MovementRequest;
	CrowdMovementRequest* MovementRequest = nullptr;

protected:

	void BeginPlay() override;
public:

	void SetDirectedCrowd(Crowd* InDirectedCrowd);
	void Tick(float DeltaTime) override;

	void ProcessCrowdMovementRequest();

	void AddMovementRequest(CrowdMovementRequest* InMovementRequest);
	void ProcessCrowdColumnMovementRequest();

	void SetCrowdColumnMovement(const TArray<AAgent*>& CurrentUnprocessedCrowdColumn, const TArray<FVector>& ColumnGoalLocations) const;
	void SetAgentMovement(AAgent* Agent, const FVector& AgentLocation, const FVector& GoalLocation) const;

	void PerformAStarMovement(const FVector& AgentLocation, const FVector& GoalLocation, AAgent* Agent) const;

	void SerializePath(Path* Path);
	Path* GetSerializedPath(int32 AgentID);

	void SetCrowdMovement(FVector);

	void OnNavigationUpdate(const FBox& Bounds);
	void ReorganizeCrowdMovement();

	void UpdateSerializedPathes();

	virtual void BeginDestroy() override;
};
