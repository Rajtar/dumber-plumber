#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DumberPlumberPipeActor.generated.h"

class ADumberPlumberCharacter;
class UCapsuleComponent;

UCLASS()
class DUMBERPLUMBER_API ADumberPlumberPipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADumberPlumberPipeActor();
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

	void DropPipe();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleCollider;

	virtual void BeginPlay() override;

private:
	void PickUpPipe(ADumberPlumberCharacter* character);

};
