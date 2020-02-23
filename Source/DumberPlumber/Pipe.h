

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <vector>

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

	FVector DetermineLocation(FVector hitLocation) const;

	void AdjustPipePreview();

	void ReleaseNeighbours();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool IsBuilt = false;

	virtual void AdjustShapeAndRotationToNeighbours();

private:

	void SetMaterial(class UMaterial* material);

	void DetermineState();

	void LinkNeighbour(APipe* pipe);

	void UnlinkNeighbour(APipe* pipe);

	void FindNeighbourBuiltPipes();

	void OneNeighbour();

	void TwoNeighbours();

	void ThreeNeighbours();

	void FourNeighbours();

	FVector getResultant();

	void setActorRotationFromVec(const FVector& vector);

	void checkIfConnected(
		std::vector<APipe*>& chain, 
		std::vector<class ASourcePipe*>& sources,
		std::vector<class ATeamDestinationPipe*>& destinations);

	void setChainConnected(
		const std::vector<APipe*>& chain,
		const std::vector<class ASourcePipe*>& sources,
		const std::vector<class ATeamDestinationPipe*>& destinations);

	std::vector<APipe*> Neighbours;

	class UAssetStorage* AssetStorage;
};
