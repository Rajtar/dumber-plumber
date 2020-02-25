


#include "PipePreview.h"
#include "Pipe.h"
#include "AssetStorage.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


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
	checkIfOverlaps();
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

void APipePreview::checkIfOverlaps()
{
	TArray<AActor*> toIgnore;
	TArray<AActor*> nearObjects;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
	UKismetSystemLibrary::BoxOverlapActors(this, this->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f), FVector(95.0f, 95.0f, 45.0f), ObjectTypes, TSubclassOf<APipe>(), toIgnore, nearObjects);

	if (nearObjects.Num() > 0)
	{
		SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Preview_Invalid));
		CanBeBuilt = false;
	}
	else
	{
		SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Preview_Valid));
		CanBeBuilt = true;
	}
}

void APipePreview::UnlinkNeighbour(APipe* pipe)
{
	Neighbours.Remove(pipe);
	AdjustShapeAndRotationToNeighbours(Neighbours);
}

bool APipePreview::GetCanBeBuilt()
{
	return CanBeBuilt;
}
