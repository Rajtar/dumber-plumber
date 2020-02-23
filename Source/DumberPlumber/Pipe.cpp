


#include "Pipe.h"
#include "SourcePipe.h"
#include "TeamDestinationPipe.h"
#include "AssetStorage.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include <algorithm>
#include <Runtime\Engine\Classes\Engine\Engine.h>

namespace {
	const float THRESHOLD = pow(2.0, 0.5) / 2.0f;
	constexpr float EPSILON(1.0f);
	constexpr float EPSILON_FOR_DIST(0.1f);
	const FVector NORTH(1.0f, 0.0f, 0.0f);
	const FVector EAST(0.0f, 1.0f, 0.0f);
	constexpr float OFFSET_ROTATION(90.0f);
}



// Sets default values
APipe::APipe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APipe::BeginPlay()
{
	Super::BeginPlay();

	AssetStorage = Cast<UAssetStorage>(GEngine->GameSingleton);

	if (AssetStorage == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Game Singleton is null"));
	}

	DetermineState();
}

void APipe::SetMaterial(UMaterial* material)
{
	if (material != nullptr)
	{
		StaticMesh->SetMaterial(0, material);
	}
}

void APipe::DetermineState()
{
	if (IsBuilt)
	{
		SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::NotConnected));
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Preview_Valid));
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APipe::LinkNeighbour(APipe* pipe)
{
	Neighbours.emplace_back(pipe);
	AdjustShapeAndRotationToNeighbours();
}

void APipe::UnlinkNeighbour(APipe* pipe)
{
	Neighbours.erase(remove(Neighbours.begin(), Neighbours.end(), pipe), Neighbours.end());
	AdjustShapeAndRotationToNeighbours();
}


void APipe::FindNeighbourBuiltPipes()
{
	TArray<AActor*> toIgnore;
	TArray<AActor*> nearObjects;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
	UKismetSystemLibrary::SphereOverlapActors(this, this->GetActorLocation(), 300.0f, ObjectTypes, TSubclassOf<APipe>(), toIgnore, nearObjects);

	for (const auto& object : nearObjects)
	{
		APipe* pipe = Cast<APipe>(object);
		if (pipe == nullptr)
		{
			continue;
		}
		if (pipe == this)
		{
			continue;
		}
		if (FVector::Dist(pipe->GetActorLocation(), GetActorLocation()) > (200.0f + EPSILON))
		{
			continue;
		}

		Neighbours.emplace_back(pipe);
		pipe->LinkNeighbour(this);
	}
}

void APipe::AdjustShapeAndRotationToNeighbours()
{
	switch (Neighbours.size())
	{
	case 0: StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight)); break;
	case 1: OneNeighbour(); break;
	case 2: TwoNeighbours(); break;
	case 3: ThreeNeighbours(); break;
	case 4: FourNeighbours(); break;
	default:
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong number of neighbours"));
		break;
	}
	}
}

void APipe::OneNeighbour()
{
	FVector resultant = getResultant();
	setActorRotationFromVec(resultant);
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight));
}

void APipe::TwoNeighbours()
{
	FVector resultant = getResultant();
	if (resultant.Size() <= EPSILON_FOR_DIST)
	{
		StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight));
		auto direction = Neighbours[0]->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		setActorRotationFromVec(direction);
	}
	else
	{
		StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Curve));
		auto direction = UKismetMathLibrary::RotateAngleAxis(resultant, -45.0f, FVector(0.0f, 0.0f, 1.0f));
		direction.Normalize();
		setActorRotationFromVec(direction);
	}
}

void APipe::ThreeNeighbours()
{
	FVector resultant = getResultant();
	setActorRotationFromVec(resultant);
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::T_Like));
}

void APipe::FourNeighbours()
{
	SetActorRotation(FQuat::Identity);
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Cross));
}

FVector APipe::getResultant()
{
	FVector resultant(FVector::ZeroVector);
	auto pipeLocation = GetActorLocation();
	for (const auto neighbour : Neighbours)
	{
		auto direction = neighbour->GetActorLocation() - pipeLocation;
		direction.Normalize();
		resultant += direction;
	}
	resultant.Normalize();
	return resultant;
}

void APipe::setActorRotationFromVec(const FVector& vector)
{
	SetActorRotation(FQuat::Identity);
	if (std::abs(FVector::Dist(vector, NORTH)) <= EPSILON_FOR_DIST)
	{
		SetActorRotation(FRotator(0.0f, OFFSET_ROTATION,  0.0f));
		return;
	}
	if (std::abs(FVector::Dist(vector, EAST)) <= EPSILON_FOR_DIST)
	{
		SetActorRotation(FRotator(0.0f, OFFSET_ROTATION * 2.0f, 0.0f));
		return;
	}
	if (std::abs(FVector::Dist(vector, -NORTH)) <= EPSILON_FOR_DIST)
	{
		SetActorRotation(FRotator(0.0f, OFFSET_ROTATION * 3.0f, 0.0f));
		return;
	}
	if (std::abs(FVector::Dist(vector, -EAST)) <= EPSILON_FOR_DIST)
	{
		SetActorRotation(FRotator(0.0f, OFFSET_ROTATION * 4.0f, 0.0f));
		return;
	}
}

bool APipe::GetIsBuilt()
{
	return IsBuilt;
}

void APipe::Build()
{
	IsBuilt = true;
	SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::NotConnected));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	std::vector<ASourcePipe*> sourcePipes;
	std::vector<ATeamDestinationPipe*> destinationPipes;
	std::vector<APipe*> chain;
	checkIfConnected(chain, sourcePipes, destinationPipes);

	if (!sourcePipes.empty() && !destinationPipes.empty())
	{
		setChainConnected(chain, sourcePipes, destinationPipes);
	}
}

void APipe::checkIfConnected(
	std::vector<APipe*>& chain, 
	std::vector<ASourcePipe*>& sources,
	std::vector<ATeamDestinationPipe*>& destinations)
{
	for (const auto& neighbour : Neighbours)
	{
		if (neighbour == nullptr)
		{
			return;
		}
		if (auto source = Cast<ASourcePipe>(neighbour))
		{
			sources.emplace_back(source);
		}
		if (auto destination = Cast<ATeamDestinationPipe>(neighbour))
		{
			destinations.emplace_back(destination);
		}
		if (std::find(chain.begin(), chain.end(), neighbour) != chain.end())
		{
			return;
		}
		chain.emplace_back(neighbour);
		neighbour->checkIfConnected(chain, sources, destinations);
	}
}

void APipe::setChainConnected(
	const std::vector<APipe*>& chain,
	const std::vector<ASourcePipe*>& sources,
	const std::vector<ATeamDestinationPipe*>& destinations)
{
	for (auto pipe : chain)
	{
		pipe->SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Connected));
	}
	for (auto pipe : sources)
	{
		pipe->SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Connected));
	}
	for (auto pipe : destinations)
	{
		pipe->SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Connected));
	}
}

FVector APipe::DetermineLocation(FVector hitLocation) const
{
	hitLocation.Z = 0.0f;
	auto location = GetTransform().GetLocation();
	location.Z = 0.0f;
	auto relativeLocation = hitLocation - location;

	auto determinant = NORTH.CosineAngle2D(relativeLocation);
	constexpr uint32_t distance = 200;
	if (determinant > THRESHOLD)
	{
		return GetTransform().GetLocation() + NORTH * distance;
	}
	if (determinant < -THRESHOLD)
	{
		return GetTransform().GetLocation() - NORTH * distance;
	}

	determinant = EAST.CosineAngle2D(relativeLocation);
	if (determinant > THRESHOLD)
	{
		return GetTransform().GetLocation() + EAST * distance;
	}
	return GetTransform().GetLocation() - EAST * distance;
}

void APipe::AdjustPipePreview()
{
	ReleaseNeighbours();
	FindNeighbourBuiltPipes();
	AdjustShapeAndRotationToNeighbours();
}

void APipe::ReleaseNeighbours()
{
	for (auto neighbour : Neighbours)
	{
		neighbour->UnlinkNeighbour(this);
	}
	Neighbours.clear();
}
