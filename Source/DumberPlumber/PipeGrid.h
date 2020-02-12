

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

	void Tick(float DeltaSeconds) override;

	void DrawGrid();

	TArray<TArray<class APipe*>> Grid;

	//TArray<AGridBase*> Grid;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	uint32 GridSize_X = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	uint32 GridSize_Y = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	uint32 GridSize = 200;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DebugDraw = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
