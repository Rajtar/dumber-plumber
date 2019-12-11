#include "DumberPlumberPipeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DumberPlumberCharacter.h"

ADumberPlumberPipeActor::ADumberPlumberPipeActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleCollider->SetCollisionResponseToAllChannels(ECR_Block);
	CapsuleCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CapsuleCollider->SetupAttachment(StaticMesh);
}

void ADumberPlumberPipeActor::BeginPlay()
{
	Super::BeginPlay();
}


void ADumberPlumberPipeActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	ADumberPlumberCharacter* PlayerCharacter = Cast<ADumberPlumberCharacter>(Other);
	if (PlayerCharacter)
	{
		PickUpPipe(PlayerCharacter);
	}
}

void ADumberPlumberPipeActor::PickUpPipe(ADumberPlumberCharacter* character)
{
	character->grabbedPipe = this;
	UE_LOG(LogTemp, Warning, TEXT("Pipe has been picked up"));
	StaticMesh->SetSimulatePhysics(false);
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->AttachToComponent(character->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
}

void ADumberPlumberPipeActor::DropPipe()
{
	UE_LOG(LogTemp, Warning, TEXT("Pipe has been dropped"));
	StaticMesh->SetSimulatePhysics(true);
	CapsuleCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));
}
