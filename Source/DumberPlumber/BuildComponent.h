

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class ADumberPlumberCharacter* ParentRef;

	UPROPERTY(EditDefaultsOnly, Category = "Pipe")
	TSubclassOf<AActor> PipeGrid;

	class APipeGrid* PipeGridRef = nullptr;

	bool IsRMBPressed = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	void SpawnPipePreview(const FVector& spawnLocation, class APipeGrid* originPipeRef);

};
