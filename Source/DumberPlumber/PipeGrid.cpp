


#include "PipeGrid.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>

// Sets default values
APipeGrid::APipeGrid()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void APipeGrid::BeginPlay()
{
	Super::BeginPlay();

	if (DebugDraw)
	{
		DrawGrid();
	}
}

void APipeGrid::Tick(float DeltaSeconds)
{

}

void APipeGrid::DrawGrid()
{
	float length_Y = GridSize_Y * GridSize;
	for (uint32 x = 0; x <= GridSize_X; ++x)
	{
		FVector LinkStart = GetActorLocation();
		FVector LinkEnd = GetActorLocation();
		LinkEnd.Y += length_Y;
		LinkStart.X += x * GridSize;
		LinkEnd.X += x * GridSize;
		DrawDebugLine(GetWorld(), LinkStart, LinkEnd, FColor::Blue, true);
	}

	float length_X = GridSize_X * GridSize;
	for (uint32 y = 0; y <= GridSize_Y; ++y)
	{
		FVector LinkStart = GetActorLocation();
		FVector LinkEnd = GetActorLocation();
		LinkEnd.X += length_X;
		LinkStart.Y += y * GridSize;
		LinkEnd.Y += y * GridSize;
		DrawDebugLine(GetWorld(), LinkStart, LinkEnd, FColor::Blue, true);
	}
}