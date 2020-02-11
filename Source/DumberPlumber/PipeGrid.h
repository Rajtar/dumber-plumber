

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeGrid.generated.h"

UCLASS()
class DUMBERPLUMBER_API APipeGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeGrid();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
