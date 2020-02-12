


#include "BuildComponent.h"
#include "DumberPlumberCharacter.h"
#include "DumberPlumberPipeActor.h"
#include "PipeGrid.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"


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

	FVector CamLoc;
	FRotator CamRot;
	ParentRef->Controller->GetPlayerViewPoint(CamLoc, CamRot);

	const FVector Target = CamLoc + CamRot.Vector() * 200;

	const UWorld* MyWorld = GetWorld();
	TArray<FHitResult> hits;
	FCollisionShape sphere = FCollisionShape::MakeSphere(100);
	MyWorld->SweepMultiByChannel(hits, CamLoc, Target, FQuat::Identity, ECollisionChannel::ECC_Visibility, sphere);

	for (const auto& hit : hits)
	{
		auto builtPipeRef = Cast<APipeGrid>(hit.Actor);
		if (builtPipeRef == nullptr)
		{
			continue;
		}
		if (PipeGridRef != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Update Location"));
			PipeGridRef->SetActorLocation(builtPipeRef->DetermineLocation(hit.Location));
			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawn Pipe Preview"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FVector location = builtPipeRef->DetermineLocation(hit.Location);
			FRotator rotation = FRotator(90.0f, 0.0f, 0.0f);
			PipeGridRef = GetWorld()->SpawnActor<AActor>(PipeGrid, location, rotation, SpawnParams);
		}
	}
}

void UBuildComponent::RightMousePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("RMB Pressed"));
	IsRMBPressed = true;
}

void UBuildComponent::RightMouseReleased()
{
	IsRMBPressed = false;
	if (PipeGridRef != nullptr)
	{
		PipeGridRef->Destroy();
		PipeGridRef = nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("RMB Released"));
}