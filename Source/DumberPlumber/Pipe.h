

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AssetStorage.h"

#include "Pipe.generated.h"


UCLASS()
class DUMBERPLUMBER_API APipe : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APipe();

	FVector DetermineLocation(FVector hitLocation) const;

	void SetMaterial(class UMaterial* material);

	virtual void UnlinkNeighbour(APipe* pipe);

	UPROPERTY(Replicated)
	class UStaticMeshComponent* StaticMesh;

	//UPROPERTY(ReplicatedUsing = TypeChanged_Client)
	PipeType PipeTypeE;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UAssetStorage* AssetStorage;

	virtual void AdjustShapeAndRotationToNeighbours(const TArray<APipe*>& neighbours);

	void FindNeighbourBuiltPipes(TArray<APipe*>& neighbours);

	virtual void LinkNeighbour(APipe* pipe);

private:

	void OneNeighbour(const TArray<APipe*>& neighbours);

	void TwoNeighbours(const TArray<APipe*>& neighbours);

	void ThreeNeighbours(const TArray<APipe*>& neighbours);

	void FourNeighbours(const TArray<APipe*>& neighbours);

	FVector getResultant(const TArray<APipe*>& neighbours);

	void setActorRotationFromVec(const FVector& vector);

	UFUNCTION()
	void TypeChanged_Client();
};
