#include "Crowd/Additional/RectangularCrowdFormation.h"

#include "Misc/Constants.h"
#include "MyProjectGameMode.h"

// ue4
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

RectangularCrowdFormation::RectangularCrowdFormation(FVector CrowdCenter, int32 CrowdMembersCount):
	CrowdFormation(CrowdCenter, CrowdMembersCount)
{
	RectangularCrowdFormation::GenerateAgentColumnsLocations(CrowdCenter, CrowdMembersCount);
}

RectangularCrowdFormation::~RectangularCrowdFormation()
{}

void RectangularCrowdFormation::GenerateAgentColumnsLocations(FVector CrowdCenter, int32 CrowdMembersCount)
{
	if (CrowdMembersCount == 0)
	{
		CrowdMembersCount = 20;
	}
	const auto GameWorld = AMyProjectGameMode::GetGameWorld();

	constexpr float RowSizeThreshold = 20.f;
	const int32 RowCount = static_cast<int32>(CrowdMembersCount/RowSizeThreshold) != 0 ? CrowdMembersCount/RowSizeThreshold : 1;

	const int32 ColumnCount = CrowdMembersCount/RowCount;

	const auto PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GameWorld, 0);

	const FRotator LeftRot(0.f, -90.f, 0.f);
	const FRotator RightRot(0.f, 90.f, 0.f);
	const FRotator BackwardRot(0.f, 180.f, 0.f);

	FVector Front = (PlayerCharacter->GetActorLocation()-CrowdCenter).GetSafeNormal();
	Front.Z = 0;
	FVector Right = RightRot.RotateVector(Front);
	Right.Z = 0;
	FVector Left = LeftRot.RotateVector(Front);
	Left.Z = 0;
	FVector Backward = BackwardRot.RotateVector(Front);
	Backward.Z = 0;

	const int32 HalfRowLength = ColumnCount*0.5*Constants::GridStep;

	const int32 FrontColumnCount = FMath::RoundHalfToEven(RowCount*0.5);
	const int32 TailColumnCount = RowCount-FrontColumnCount;

	const FVector TailRowLeftBound = Backward*TailColumnCount*Constants::GridStep+Left*HalfRowLength;
	const FVector FrontRowRightBound = Front*FrontColumnCount*Constants::GridStep+Right*HalfRowLength-Constants::
		DebugVectorZOffset;

	const FVector ColumnStepVector = Left*Constants::GridStep;
	const FVector RowStepVector = Backward*Constants::GridStep;

	FVector RowStartPosition = FrontRowRightBound;
	for (int32 Row = 0; Row<RowCount; Row++)
	{
		Offsets.Emplace(TArray<FVector>());

		for (int32 Column = 0; Column<ColumnCount; Column++)
		{
			FVector NewPosition = RowStartPosition+ColumnStepVector*Column;
			NewPosition.Z = 0;

			Offsets[Row].Emplace(NewPosition);
			//DrawDebugLine(GameWorld, Offsets[Row][Column]+Constants::DebugVectorZOffset*2,
			//              Offsets[Row][Column]-Constants::DebugVectorZOffset,
			//              FColor::Red, false, 3.f, 0, 20);
		}
		RowStartPosition += RowStepVector;
	}

	//DrawDebugLine(GameWorld, TailRowLeftBound+Constants::DebugVectorZOffset*2, TailRowLeftBound-Constants::DebugVectorZOffset,
	//              FColor::White, false, 3.f, 0, 20);
	//
	//DrawDebugLine(GameWorld, FrontRowRightBound+Constants::DebugVectorZOffset*2, FrontRowRightBound-Constants::DebugVectorZOffset,
	//              FColor::Black, false, 3.f, 0, 20);

	//Offsets.Emplace(TArray<FVector>());
	////Offsets[0].Emplace(CrowdCenter - FVector{0,0,200});
	//Offsets[0].Emplace(FVector{0.f, 0.f, -200});

	const FVector XOffset = {0, 0, 100};
}
