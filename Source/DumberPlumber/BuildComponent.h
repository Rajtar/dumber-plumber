

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUMBERPLUMBER_API UBuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildComponent();

	void Update();

	void LeftMousePressed();

	void RightMousePressed();

	void RightMouseReleased();

	bool GetIsInBuildMode();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class ADumberPlumberCharacter* ParentRef;

	UPROPERTY(EditDefaultsOnly, Category = "Pipe")
	TSubclassOf<AActor> Pipe;

	class APipe* PipeRef = nullptr;

	bool IsRMBPressed = false;

	bool IsInBuildMode = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	void AdjustPipePreview(const FVector& nearestHitLocation, const APipe* nearestBuiltPipe);

	void SpawnPipePreview(const FVector& spawnLocation, class APipe* originPipeRef);

	TArray<FHitResult> FindObejctsAroundRayInRange(const float range) const;

	class APipe* FindNearestPipe(const TArray<FHitResult>& hits, FVector& outNearestHit);

	FVector LastPipeLocation;

};
