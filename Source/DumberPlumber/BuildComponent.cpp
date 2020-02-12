


#include "BuildComponent.h"
#include "DumberPlumberCharacter.h"
#include "DumberPlumberPipeActor.h"
#include "Pipe.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Math/NumericLimits.h"


namespace {
	constexpr uint32_t BUILDING_DISTANCE(450);
}

// Sets default values for this component's properties
UBuildComponent::UBuildComponent()
{
	
}


void UBuildComponent::BeginPlay()
{
	Super::BeginPlay();
	ParentRef = Cast<ADumberPlumberCharacter>(GetOwner());

	if (ParentRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Build Component has no parent of type DumberPlumber"));
	}
}


// Called every frame
void UBuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBuildComponent::SpawnPipePreview(const FVector& spawnLocation, APipe* originPipeRef)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn Pipe Preview"));
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector location = originPipeRef->DetermineLocation(spawnLocation);
	FRotator rotation = FRotator(90.0f, 0.0f, 0.0f);
	PipeRef = GetWorld()->SpawnActor<APipe>(Pipe, location, rotation, SpawnParams);
}

void UBuildComponent::Update()
{
	if (!IsRMBPressed)
	{
		return;
	}

	FVector CamLoc;
	FRotator CamRot;
	ParentRef->Controller->GetPlayerViewPoint(CamLoc, CamRot);

	const FVector Target = CamLoc + CamRot.Vector() * BUILDING_DISTANCE;

	const UWorld* MyWorld = GetWorld();
	TArray<FHitResult> hits;
	FCollisionShape sphere = FCollisionShape::MakeSphere(100);
	MyWorld->SweepMultiByChannel(hits, CamLoc, Target, FQuat::Identity, ECollisionChannel::ECC_Visibility, sphere);

	if (hits.Num() == 0)
	{
		return;
	}

	APipe* nearestBuiltPipeRef = nullptr;
	FVector nearestHitLocation;
	float minDistance = TNumericLimits<float>::Max();
	for (const auto& hit : hits)
	{
		auto builtPipeRef = Cast<APipe>(hit.Actor);
		if (builtPipeRef == nullptr)
		{
			continue;
		}
		float distance = FVector::Dist(hit.Location, builtPipeRef->GetActorLocation());
		if (distance < minDistance)
		{
			nearestBuiltPipeRef = builtPipeRef;
			nearestHitLocation = hit.Location;
		}
	}

	if (nearestBuiltPipeRef == nullptr)
	{
		return;
	}

	if (PipeRef != nullptr)
	{
		PipeRef->SetActorLocation(nearestBuiltPipeRef->DetermineLocation(nearestHitLocation));
	}
	else
	{
		SpawnPipePreview(nearestHitLocation, nearestBuiltPipeRef);
	}
}

void UBuildComponent::LeftMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("LMB Pressed"));
	if (PipeRef == nullptr)
	{
		return;
	}

	PipeRef->Build();
	PipeRef = nullptr;
}

void UBuildComponent::RightMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("RMB Pressed"));
	IsRMBPressed = true;
}

void UBuildComponent::RightMouseReleased()
{
	IsRMBPressed = false;
	if (PipeRef != nullptr)
	{
		PipeRef->Destroy();
		PipeRef = nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("RMB Released"));
}