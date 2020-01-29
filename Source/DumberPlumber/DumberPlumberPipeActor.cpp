#include "DumberPlumberPipeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DumberPlumberCharacter.h"
#include "Net/UnrealNetwork.h"

ADumberPlumberPipeActor::ADumberPlumberPipeActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleCollider->SetCollisionResponseToAllChannels(ECR_Block);
	CapsuleCollider->SetupAttachment(StaticMesh);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void ADumberPlumberPipeActor::BeginPlay()
{
	Super::BeginPlay();
}


void ADumberPlumberPipeActor::Interact(ACharacter* User)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
	PickUpPipe(User);
}

void ADumberPlumberPipeActor::MarkAsFocused()
{
	StaticMesh->SetRenderCustomDepth(true);
}

void ADumberPlumberPipeActor::UnmarkAsFocused()
{
	StaticMesh->SetRenderCustomDepth(false);
}

void ADumberPlumberPipeActor::PickUpPipe(ACharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Pick Up"));
	PlayerCharacter = Cast<ADumberPlumberCharacter>(Character);
	if (PlayerCharacter)
	{
		PlayerCharacter->GrabbedPipe = this;
		StaticMesh->SetSimulatePhysics(false);
		CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		StaticMesh->AttachToComponent(Character->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	}
}

void ADumberPlumberPipeActor::DropPipe()
{
	PlayerCharacter = nullptr;
	StaticMesh->SetSimulatePhysics(true);
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));
}

void ADumberPlumberPipeActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADumberPlumberPipeActor, StaticMesh);
	DOREPLIFETIME(ADumberPlumberPipeActor, CapsuleCollider);
	DOREPLIFETIME(ADumberPlumberPipeActor, PlayerCharacter);
}
