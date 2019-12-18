#include "DumberPlumberPipeSocketMock.h"
#include "Components/BoxComponent.h"
#include "DumberPlumberPipeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

ADumberPlumberPipeSocketMock::ADumberPlumberPipeSocketMock()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollider->SetupAttachment(StaticMesh);
}


void ADumberPlumberPipeSocketMock::DeactivateParticles()
{
	GetComponents<UParticleSystemComponent>(ParticleSystems);
	for (UParticleSystemComponent* particleSystem : ParticleSystems) {
		UE_LOG(LogTemp, Warning, TEXT("DISABLING PARTICLE!!!"));
		particleSystem->Deactivate();
	}
}

void ADumberPlumberPipeSocketMock::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ADumberPlumberPipeActor* pipe = Cast<ADumberPlumberPipeActor>(OtherActor);
	if (pipe)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pipe has been placed"));
		StaticMesh->SetVisibility(true);
		pipe->SetActorHiddenInGame(true);
		BoxCollider->SetCollisionResponseToAllChannels(ECR_Block);

		DeactivateParticles();
	}
}

void ADumberPlumberPipeSocketMock::BeginPlay()
{
	Super::BeginPlay();
	
}
