


#include "BuildComponent.h"
#include "DumberPlumberCharacter.h"
#include "DumberPlumberPipeActor.h"
#include "Pipe.h"
#include "PipePreview.h"
#include "PipeBuilt.h"
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

void UBuildComponent::Update()
{
	if (!IsRMBPressed)
	{
		return;
	}

	if (!IsInDebugMode)
	{
		if (ParentRef->GrabbedPipe == nullptr)
		{
			return;
		}
	}

	TArray<FHitResult> hits = FindObejctsAroundRayInRange(100.0f);

	if (hits.Num() == 0)
	{
		return;
	}

	FVector nearestHitLocation;
	APipe* nearestBuiltPipe = FindNearestPipe(hits, nearestHitLocation);

	if (nearestBuiltPipe == nullptr)
	{
		return;
	}

	IsInBuildMode = true;

	if (PipePreview != nullptr)
	{
		AdjustPipePreview(nearestHitLocation, nearestBuiltPipe);
	}
	else
	{
		SpawnPipePreview(nearestHitLocation, nearestBuiltPipe);
	}
}

void UBuildComponent::LeftMousePressed()
{
	if (PipePreview == nullptr)
	{
		return;
	}

	SpawnPipeBuilt(PipePreview->GetActorLocation(), PipePreview->GetActorRotation());
	PipePreview->ReleaseNeighbours();
	PipePreview->Destroy();
	PipePreview = nullptr;
	LastPipeLocation = FVector::ZeroVector;

	if (ParentRef->GrabbedPipe != nullptr)
	{
		ParentRef->GrabbedPipe->Destroy();
		ParentRef->GrabbedPipe = nullptr;
	}
	IsInBuildMode = false;
}

void UBuildComponent::RightMousePressed()
{
	IsRMBPressed = true;
}

void UBuildComponent::RightMouseReleased()
{
	IsRMBPressed = false;
	IsInBuildMode = false;
	if (PipePreview != nullptr)
	{
		PipePreview->ReleaseNeighbours();
		PipePreview->Destroy();
		PipePreview = nullptr;
		LastPipeLocation = FVector::ZeroVector;
	}
}

void UBuildComponent::ToggleDebugMode()
{
	IsInDebugMode = !IsInDebugMode;
	UE_LOG(LogTemp, Warning, TEXT("Toggle Debug Mode current state: %s"), IsInDebugMode ? TEXT("True") : TEXT("False"));
}

bool UBuildComponent::GetIsInBuildMode()
{
	return IsInBuildMode;
}

void UBuildComponent::AdjustPipePreview(const FVector& nearestHitLocation, const APipe* nearestBuiltPipe)
{
	auto newPipeLocation = nearestBuiltPipe->DetermineLocation(nearestHitLocation);
	if (newPipeLocation == LastPipeLocation)
	{
		return;
	}
	PipePreview->SetActorLocation(newPipeLocation);
	PipePreview->AdjustPipePreview();
	LastPipeLocation = newPipeLocation;
}

void UBuildComponent::SpawnPipePreview(const FVector& spawnLocation, APipe* originPipeRef)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector location = originPipeRef->DetermineLocation(spawnLocation);
	FRotator rotation = FRotator(90.0f, 0.0f, 0.0f);
	PipePreview = GetWorld()->SpawnActor<APipePreview>(PipePreviewType, location, rotation, SpawnParams);
}

void UBuildComponent::SpawnPipeBuilt(const FVector& location, const FRotator& rotation)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<APipeBuilt>(PipeBuiltType, location, rotation, SpawnParams);
}

TArray<FHitResult> UBuildComponent::FindObejctsAroundRayInRange(const float range) const
{
	FVector CamLoc;
	FRotator CamRot;
	ParentRef->Controller->GetPlayerViewPoint(CamLoc, CamRot);

	const FVector Target = CamLoc + CamRot.Vector() * BUILDING_DISTANCE;

	const UWorld* MyWorld = GetWorld();
	TArray<FHitResult> hits;
	FCollisionShape sphere = FCollisionShape::MakeSphere(100);
	MyWorld->SweepMultiByChannel(hits, CamLoc, Target, FQuat::Identity, ECollisionChannel::ECC_Visibility, sphere);

	return hits;
}

APipe* UBuildComponent::FindNearestPipe(const TArray<FHitResult>& hits, FVector& outNearestHit)
{
	APipe* nearestBuiltPipe = nullptr;
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
			nearestBuiltPipe = builtPipeRef;
			outNearestHit = hit.Location;
		}
	}
	return nearestBuiltPipe;
}
