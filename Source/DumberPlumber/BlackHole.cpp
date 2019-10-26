// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DumberPlumberCharacter.h"

// Sets default values for this component's properties
ABlackHole::ABlackHole()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;

	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphereComponent->SetSphereRadius(100);
	InnerSphereComponent->SetupAttachment(MeshComponent);

	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
	
	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphereComponent->SetSphereRadius(3000);
	OuterSphereComponent->SetupAttachment(MeshComponent);
}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && !Cast<ADumberPlumberCharacter>(OtherActor))
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OuterSphereComponent->GetOverlappingComponents(OverlappingComponents);

	for(int32 i = 0; i<OverlappingComponents.Num(); i++)
	{
		UPrimitiveComponent* PrimitiveComponent = OverlappingComponents[i];
		if(PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphereComponent->GetScaledSphereRadius();
			const float ForceStrength = -2000;

			PrimitiveComponent->AddRadialForce(GetActorLocation(),SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

