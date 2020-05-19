#include "Agent.h"

#include "Algo/Path.h"
#include "Algo/GraphNode.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"

void AAgent::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		return;
	}
	
	if (MovementResult != EPathFollowingResult::Success)
	{
		MovementInterruptionTime = GetWorld()->GetRealTimeSeconds();
		bMovementInterrupter = true;
		AIController->ReceiveMoveCompleted.Clear();
		return;	
	}

	bMovementInterrupter = false;
	AIController->ReceiveMoveCompleted.Clear();

	const auto NextGraphNode = CurrentPath->GetNextGraphNode();
	if (!NextGraphNode)
	{
		return;
	}
	const auto NextMovementLocation = NextGraphNode->GetLocation();
	MoveToLocation(NextMovementLocation);
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	constexpr float TimeToPassSec = 0.5f;
	if (bMovementInterrupter && MovementInterruptionTime <= GetWorld()->GetTimeSeconds() - TimeToPassSec)
	{
		const auto Node = CurrentPath->GetNextGraphNodeSafe();
		if (!Node)
		{
			return;
		}

		MoveToLocation(Node->GetLocation());
	}

	// todo : add delayed move to
	//const FVector Offset = {15,15,0};
	//MoveToLocation(GetLocation() + Offset);
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
	// Add some check lvl
	const auto AcceptanceRadius = 5.f;
	auto Result = AIController->MoveToLocation(GoalLocation, AcceptanceRadius, false, true, true, true);//, NavFilterSubClass);

	//DrawDebugLine(GetWorld(), GoalLocation+Constants::ZOffset, GoalLocation-ZOffset, FColor::Black, true, 3.f, 0, 20);		

	AIController->ReceiveMoveCompleted.AddDynamic(this, &AAgent::OnMoveCompleted);
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

AAgent::AAgent()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	GetCharacterMovement()->MaxAcceleration = 100000.f;
}

void AAgent::BeginDestroy()
{
	Super::BeginDestroy();
}

void AAgent::Init()
{}

FVector AAgent::GetLocation() const
{
	return GetActorLocation();
}
