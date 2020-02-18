


#include "Pipe.h"
#include "SourcePipe.h"
#include "TeamDestinationPipe.h"

#include "Kismet/KismetSystemLibrary.h"
#include <algorithm>

namespace {
	const float THRESHOLD = pow(2.0, 0.5) / 2.0f;
	const float EPSILON = 10.0f;
	const FVector NORTH(1.0f, 0.0f, 0.0f);
	const FVector EAST(0.0f, 1.0f, 0.0f);
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
	}

	ASourcePipe* sourcePipe = nullptr;
	ATeamDestinationPipe* destinationPipe = nullptr;
	std::vector<APipe*> chain;
	checkIfConnected(chain, sourcePipe, destinationPipe);
}

void APipe::checkIfConnected(std::vector<APipe*>& chain, ASourcePipe* source, ATeamDestinationPipe* destination)
{
	UE_LOG(LogTemp, Error, TEXT("checkIfConnected: %s"), *this->GetName());
	for (const auto& neighbour : Neighbours)
	{
		UE_LOG(LogTemp, Warning, TEXT("checking neighbour: %s"), *neighbour->GetName())
		if (neighbour == nullptr)
		{
			return;
		}
		if ((source = Cast<ASourcePipe>(neighbour)) != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found source: %s"), *source->GetName());
			return;
		}
		if ((destination = Cast<ATeamDestinationPipe>(neighbour)) != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found destination: %s"), *destination->GetName())
			return;
		}
		if (std::find(chain.begin(), chain.end(), neighbour) != chain.end())
		{
			UE_LOG(LogTemp, Warning, TEXT("already in chain: %s"), *neighbour->GetName())
			return;
		}
		chain.emplace_back(neighbour);
		neighbour->checkIfConnected(chain, source, destination);
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