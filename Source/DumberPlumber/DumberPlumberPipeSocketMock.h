#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DumberPlumberPipeSocketMock.generated.h"

class UBoxComponent;
class UParticleSystemComponent;

UCLASS()
class DUMBERPLUMBER_API ADumberPlumberPipeSocketMock : public AActor
{
	GENERATED_BODY()
	
public:	
	ADumberPlumberPipeSocketMock();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollider;

	TArray<UParticleSystemComponent*> ParticleSystems;

	virtual void BeginPlay() override;

private:
	void DeactivateParticles();
};
