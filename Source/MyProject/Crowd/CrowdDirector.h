#pragma once

#include "GameFramework/Actor.h"
#include "NavigationSystem.h"

#include "Queue.h"

#include "CrowdDirector.generated.h"

struct Path;
class Crowd;


class CrowdMovementRequest;
UCLASS()
	class ACrowdDirector : public AActor
{
	GENERATED_BODY()

private:

	//UPROPERTY()
	TMap<int32, Path*> AgentPaths;
	//std::map<int32, Path*> AgentPaths;

	Crowd* DirectedCrowd = nullptr;

	TQueue<TUniquePtr<CrowdMovementRequest>> MovementRequests;

protected:

	void BeginPlay() override;
public:

	void SetDirectedCrowd(Crowd* InDirectedCrowd);
	void Tick(float DeltaTime) override;

	void SerializePath(Path* Path);
	Path* GetSerializedPath(int32 AgentID);

	void SetCrowdMovement(FVector);

	void ReorganizeCrowdMovement();

	void Init()
	{
		
	}

	void OnNavigationUpdate(const FBox& Bounds)
	{
		ReorganizeCrowdMovement();
	}

	void UpdatePathMap();

	virtual void BeginDestroy() override;
};
