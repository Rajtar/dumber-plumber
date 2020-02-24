


#include "Pipe.h"
#include "SourcePipe.h"
#include "TeamDestinationPipe.h"
#include "AssetStorage.h"
#include "PipeBuilt.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include <algorithm>
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include "Net/UnrealNetwork.h"

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

	SetReplicates(true);
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
}

void APipe::SetMaterial(UMaterial* material)
{
	if (material != nullptr)
	{
		StaticMesh->SetMaterial(0, material);
	}
}

void APipe::LinkNeighbour(APipe* pipe)
{
	UE_LOG(LogTemp, Error, TEXT("Unimplemented Link"));
}

void APipe::UnlinkNeighbour(APipe* pipe)
{
	UE_LOG(LogTemp, Error, TEXT("Unimplemented Unlink"));
}

void APipe::FindNeighbourBuiltPipes(TArray<APipe*>& neighbours)
{
	UE_LOG(LogTemp, Warning, TEXT("Find neighbours"));
	TArray<AActor*> toIgnore;
	TArray<AActor*> nearObjects;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery2);
	UKismetSystemLibrary::SphereOverlapActors(this, this->GetActorLocation(), 300.0f, ObjectTypes, TSubclassOf<APipe>(), toIgnore, nearObjects);

	for (const auto& object : nearObjects)
	{
		APipe* pipe = Cast<APipeBuilt>(object);
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
		UE_LOG(LogTemp, Warning, TEXT("Neighbour found: %s"), *pipe->GetName());
		neighbours.Add(pipe);
		pipe->LinkNeighbour(this);
	}
}

void APipe::AdjustShapeAndRotationToNeighbours(const TArray<APipe*>& neighbours)
{
	UE_LOG(LogTemp, Warning, TEXT("Number of neighbours: %d"), neighbours.Num());
	switch (neighbours.Num())
	{
	case 0: StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight)); break;
	case 1: OneNeighbour(neighbours); break;
	case 2: TwoNeighbours(neighbours); break;
	case 3: ThreeNeighbours(neighbours); break;
	case 4: FourNeighbours(neighbours); break;
	default:
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong number of neighbours"));
		break;
	}
	}
}

void APipe::OneNeighbour(const TArray<APipe*>& neighbours)
{
	FVector resultant = getResultant(neighbours);
	setActorRotationFromVec(resultant);
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight));
}

void APipe::TwoNeighbours(const TArray<APipe*>& neighbours)
{
	FVector resultant = getResultant(neighbours);
	if (resultant.Size() <= EPSILON_FOR_DIST)
	{
		StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Straight));
		auto direction = neighbours[0]->GetActorLocation() - GetActorLocation();
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

void APipe::ThreeNeighbours(const TArray<APipe*>& neighbours)
{
	FVector resultant = getResultant(neighbours);
	setActorRotationFromVec(resultant);
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::T_Like));
}

void APipe::FourNeighbours(const TArray<APipe*>& neighbours)
{
	SetActorRotation(FQuat::Identity);
	StaticMesh->SetStaticMesh(*AssetStorage->PipeMeshes.Find(PipeType::Cross));
}

FVector APipe::getResultant(const TArray<APipe*>& neighbours)
{
	FVector resultant(FVector::ZeroVector);
	auto pipeLocation = GetActorLocation();
	for (const auto neighbour : neighbours)
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

void APipe::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APipe, StaticMesh);
}