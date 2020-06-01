#include "Agent.h"

#include "Algo/Path.h"
#include "Algo/GraphNode.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Misc/Constants.h"

AAgent::AAgent()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->MaxAcceleration = 100000.f;
}

AAgent::~AAgent()
{}

void AAgent::BeginDestroy()
{
	Super::BeginDestroy();
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	constexpr float TimeToPassSec = 0.5f;
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (bMovementInterrupter&&MovementInterruptionTime<=CurrentTime-TimeToPassSec)
	{
		const auto Node = CurrentPath->GetNextGraphNodeSafe();
		if (!Node)
		{
			return;
		}

		MoveToLocation(Node->GetLocation());
	}
}

void AAgent::SetAgentIndex(int32 Index)
{
	AgentIndex = Index;
}

int32 AAgent::GetAgentIndex() const
{
	return AgentIndex;
}

void AAgent::SetPath(Path* Path)
{
	CurrentPath = Path;
	CurrentPath->PathOwner = this;
}

Path* AAgent::GetPath() const
{
	return CurrentPath;
}

void AAgent::MoveToLocation(const FVector& GoalLocation)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		return;
	}
	
	constexpr float AcceptanceRadius = Constants::GridStep;

	if (!AIController->ReceiveMoveCompleted.IsBound())
	{
		AIController->ReceiveMoveCompleted.AddDynamic(this, &AAgent::OnMoveCompleted);
	}

	const EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(GoalLocation, AcceptanceRadius, false);
	if (Result!=EPathFollowingRequestResult::RequestSuccessful)
	{
		int32 Debug = 0;
	}
}

// todo : customize
void AAgent::AbortMovement() const
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->StopMovement();
	}
}

void AAgent::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		return;
	}

	//if (MovementResult!=EPathFollowingResult::Success)
	//{
	//	MovementInterruptionTime = GetWorld()->GetTimeSeconds();
	//	bMovementInterrupter = true;
	//	return;
	//}
	//
	//bMovementInterrupter = false;
	const auto NextGraphNode = CurrentPath->GetNextGraphNode();
	if (!NextGraphNode)
	{
		AIController->ReceiveMoveCompleted.Clear();
		return;
	}
	const auto NextMovementLocation = NextGraphNode->GetLocation();
	MoveToLocation(NextMovementLocation);
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();
}
