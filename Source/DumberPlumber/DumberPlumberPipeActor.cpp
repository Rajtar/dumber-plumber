#include "DumberPlumberPipeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DumberPlumberCharacter.h"

ADumberPlumberPipeActor::ADumberPlumberPipeActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleCollider->SetCollisionResponseToAllChannels(ECR_Block);
	CapsuleCollider->SetupAttachment(StaticMesh);
}

void ADumberPlumberPipeActor::BeginPlay()
{
	Super::BeginPlay();
}


void ADumberPlumberPipeActor::Interact(ACharacter* User)
{
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

void ADumberPlumberPipeActor::PickUpPipe(ACharacter* character)
{
	ADumberPlumberCharacter* PlayerCharacter = Cast<ADumberPlumberCharacter>(character);
	if (PlayerCharacter)
	{
		PlayerCharacter->grabbedPipe = this;
		StaticMesh->SetSimulatePhysics(false);
		CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		StaticMesh->AttachToComponent(character->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	}
}

void ADumberPlumberPipeActor::DropPipe() const
{
	StaticMesh->SetSimulatePhysics(true);
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));
}
