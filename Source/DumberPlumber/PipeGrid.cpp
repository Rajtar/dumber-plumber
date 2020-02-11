


#include "PipeGrid.h"

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
	
}

// Called every frame
//void APipeGrid::Tick(float DeltaTime)
//{
//	//Super::Tick(DeltaTime);
//
//}

