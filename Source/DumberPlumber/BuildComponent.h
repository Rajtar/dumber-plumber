

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

	void ToggleDebugMode();

	bool GetIsInBuildMode();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class ADumberPlumberCharacter* ParentRef;

	UPROPERTY(EditDefaultsOnly, Category = "Pipe")
	TSubclassOf<AActor> PipePreviewType;

	UPROPERTY(EditDefaultsOnly, Category = "Pipe")
	TSubclassOf<AActor> PipeBuiltType;

	class APipePreview* PipePreview = nullptr;

	bool IsRMBPressed = false;

	bool IsInBuildMode = false;

	bool IsInDebugMode = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	void AdjustPipePreview(const FVector& nearestHitLocation, const class APipe* nearestBuiltPipe);

	void SpawnPipePreview(const FVector& spawnLocation, class APipe* originPipeRef);

	void SpawnPipeBuilt(const FVector& location, const FRotator& rotation);

	TArray<FHitResult> FindObejctsAroundRayInRange(const float range) const;

	class APipe* FindNearestPipe(const TArray<FHitResult>& hits, FVector& outNearestHit);

	FVector LastPipeLocation;

};
