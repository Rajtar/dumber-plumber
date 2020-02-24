


#include "PipePreview.h"
#include "Pipe.h"
#include "AssetStorage.h"


APipePreview::APipePreview() : Super()
{
}

void APipePreview::BeginPlay()
{
	Super::BeginPlay();

	SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Preview_Valid));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APipePreview::AdjustPipePreview()
{
	ReleaseNeighbours();
	FindNeighbourBuiltPipes(Neighbours);
	AdjustShapeAndRotationToNeighbours(Neighbours);
}

void APipePreview::ReleaseNeighbours()
{
	UE_LOG(LogTemp, Warning, TEXT("ReleaseNeighbours: %d"), Neighbours.Num());
	for (auto neighbour : Neighbours)
	{
		neighbour->UnlinkNeighbour(this);
	}
	Neighbours.Empty();
}

void APipePreview::LinkNeighbour(APipe* pipe)
{
	Neighbours.Add(pipe);
	AdjustShapeAndRotationToNeighbours(Neighbours);
}

void APipePreview::UnlinkNeighbour(APipe* pipe)
{
	Neighbours.Remove(pipe);
	AdjustShapeAndRotationToNeighbours(Neighbours);
}