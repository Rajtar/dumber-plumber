


#include "PipeGrid.h"

namespace {
	const float THRESHOLD = pow(2.0, 0.5) / 2.0f;
	const FVector NORTH(1.0f, 0.0f, 0.0f);
	const FVector EAST(0.0f, 1.0f, 0.0f);
}


// Sets default values
APipeGrid::APipeGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APipeGrid::BeginPlay()
{
	Super::BeginPlay();
	
	DetermineState();
}

void APipeGrid::SetMaterial(UMaterial* material)
{
	if (material != nullptr)
	{
		StaticMesh->SetMaterial(0, material);
	}
}

void APipeGrid::DetermineState()
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

bool APipeGrid::GetIsBuilt()
{
	return IsBuilt;
}

void APipeGrid::Build()
{
	IsBuilt = true;
	SetMaterial(BuiltMaterial);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

FVector APipeGrid::DetermineLocation(FVector hitLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("forward: %s"), *GetActorForwardVector().ToString());
	UE_LOG(LogTemp, Warning, TEXT("up: %s"), *GetActorUpVector().ToString());
	UE_LOG(LogTemp, Warning, TEXT("right: %s"), *GetActorRightVector().ToString());

	hitLocation.Z = 0.0f;
	auto location = GetTransform().GetLocation();
	location.Z = 0.0f;
	auto relativeLocation = hitLocation - location;
	UE_LOG(LogTemp, Warning, TEXT("relativeLocation: %s"), *relativeLocation.ToString());


	auto determinant = NORTH.CosineAngle2D(relativeLocation);
	UE_LOG(LogTemp, Warning, TEXT("forward determinant: %s"), *FString::SanitizeFloat(determinant));
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
	UE_LOG(LogTemp, Warning, TEXT("up determinant: %s"), *FString::SanitizeFloat(determinant));
	if (determinant > THRESHOLD)
	{
		return GetTransform().GetLocation() + EAST * distance;
	}
	return GetTransform().GetLocation() - EAST * distance;
}