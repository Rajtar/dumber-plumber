


#include "Pipe.h"
#include "SourcePipe.h"
#include "TeamDestinationPipe.h"
#include "AssetStorage.h"

#include "Kismet/KismetSystemLibrary.h"
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
		SetMaterial(BuiltMaterial);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		SetMaterial(PreviewMaterial);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APipe::LinkNeighbour(APipe* pipe)
{
	Neighbours.emplace_back(pipe);
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
		UE_LOG(LogTemp, Warning, TEXT("pipe candidate: %s"), *object->GetName());

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

		UE_LOG(LogTemp, Warning, TEXT("Add pipe: %s as neighbour"), *object->GetName());

		Neighbours.emplace_back(pipe);
		pipe->LinkNeighbour(this);
	}
}

void APipe::AdjustShapeAndRotationToNeighbours()
{
	UE_LOG(LogTemp, Warning, TEXT("AdjustShapeToNeighbours: size of neighbours = %d"), Neighbours.size());

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

	UE_LOG(LogTemp, Warning, TEXT("AdjustShapeToNeighbours END"));
}

void APipe::OneNeighbour()
{
	UE_LOG(LogTemp, Warning, TEXT("OneNeighbour"));
	FVector resultant = getResultant();
	//SetActorRelativeRotation(getDesiredRotationFromVec(resultant));
	SetActorRotation(FQuat::Identity);
	SetActorRotation(getDesiredRotationFromVec(resultant));
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight));
}

void APipe::TwoNeighbours()
{
	UE_LOG(LogTemp, Warning, TEXT("TwoNeighbours"));
	FVector resultant = getResultant();
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Curve));
}

void APipe::ThreeNeighbours()
{
	UE_LOG(LogTemp, Warning, TEXT("ThreeNeighbours"));
	FVector resultant = getResultant();
	//SetActorRelativeRotation(getDesiredRotationFromVec(resultant));
	SetActorRotation(FQuat::Identity);
	SetActorRotation(getDesiredRotationFromVec(resultant));
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::T_Like));
}

void APipe::FourNeighbours()
{
	UE_LOG(LogTemp, Warning, TEXT("FourNeighbours"));
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

FRotator APipe::getDesiredRotationFromVec(const FVector& vector)
{
	UE_LOG(LogTemp, Warning, TEXT("resultant vector: %s"), *vector.ToString());

	if (std::abs(FVector::Dist(vector, NORTH)) <= EPSILON_FOR_DIST)
	{
		auto rotator = FRotator(0.0f, OFFSET_ROTATION * -3.0f, 0.0f );
		UE_LOG(LogTemp, Warning, TEXT("NORTH rotator: %s"), *rotator.ToString());
		return rotator;
	}
	if (std::abs(FVector::Dist(vector, EAST)) <= EPSILON_FOR_DIST)
	{
		auto rotator = FRotator(0.0f, 0.0f, OFFSET_ROTATION * -2.0f);
		UE_LOG(LogTemp, Warning, TEXT("EAST rotator: %s"), *rotator.ToString());
		return rotator;
	}
	if (std::abs(FVector::Dist(vector, -NORTH)) <= EPSILON_FOR_DIST)
	{
		auto rotator = FRotator(0.0f, -OFFSET_ROTATION , 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("SOUTH rotator: %s"), *rotator.ToString());
		return rotator;
	}
	if (std::abs(FVector::Dist(vector, -EAST)) <= EPSILON_FOR_DIST)
	{
		auto rotator = FRotator(0.0f, 0.0f, OFFSET_ROTATION * 4.0f);
		UE_LOG(LogTemp, Warning, TEXT("WEST rotator: %s"), *rotator.ToString());
		return rotator;
	}
	return FRotator();
}

bool APipe::GetIsBuilt()
{
	return IsBuilt;
}

void APipe::Build()
{
	UE_LOG(LogTemp, Warning, TEXT("build: %s"), *this->GetName());
	IsBuilt = true;
	SetMaterial(BuiltMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	FindNeighbourBuiltPipes();

	std::vector<ASourcePipe*> sourcePipes;
	std::vector<ATeamDestinationPipe*> destinationPipes;
	std::vector<APipe*> chain;
	checkIfConnected(chain, sourcePipes, destinationPipes);

	AdjustShapeAndRotationToNeighbours();
}

void APipe::checkIfConnected(
	std::vector<APipe*>& chain, 
	std::vector<ASourcePipe*> sources,
	std::vector<ATeamDestinationPipe*> destinations)
{
	for (const auto& neighbour : Neighbours)
	{
		if (neighbour == nullptr)
		{
			return;
		}
		if (auto source = Cast<ASourcePipe>(neighbour))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found source: %s"), *source->GetName());
			sources.emplace_back(source);
			return;
		}
		if (auto destination = Cast<ATeamDestinationPipe>(neighbour))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found destination: %s"), *destination->GetName());
			destinations.emplace_back(destination);
			return;
		}
		if (std::find(chain.begin(), chain.end(), neighbour) != chain.end())
		{
			return;
		}
		chain.emplace_back(neighbour);
		neighbour->checkIfConnected(chain, sources, destinations);
	}
}

FVector APipe::DetermineLocation(FVector hitLocation)
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