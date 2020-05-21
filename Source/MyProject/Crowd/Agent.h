#pragma once

#include "Paths.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "Agent.generated.h"

struct Path;

UCLASS()
	class AAgent : public ACharacter
{
	GENERATED_BODY()

public:
	AAgent();
	virtual ~AAgent();
	virtual void BeginDestroy() override;

	void Tick(float DeltaTime) override;

	void SetAgentIndex(int32 Index);
	int32 GetAgentIndex() const;

	void SetPath(Path* Path);
	Path* GetPath() const;

	void MoveToLocation(const FVector& GoalLocation);
	void AbortMovement() const;

private:
	Path* CurrentPath = nullptr;
	bool bMovementInterrupter = false;
	float MovementInterruptionTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	int32 AgentIndex = -1;

protected:
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);
	void BeginPlay() override;
};
