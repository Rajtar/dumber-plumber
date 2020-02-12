

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pipe.generated.h"

UCLASS()
class DUMBERPLUMBER_API APipe : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APipe();

	bool GetIsBuilt();

	void Build();

	FVector DetermineLocation(FVector hitLocation);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UMaterial* BuiltMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UMaterial* PreviewMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool IsBuilt = false;

	void SetMaterial(class UMaterial* material);

	void DetermineState();

private:

	APipe* Left;
	APipe* Right;
	APipe* Front;
	APipe* Back;
};
