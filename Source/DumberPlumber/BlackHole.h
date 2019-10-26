// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "BlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class DUMBERPLUMBER_API ABlackHole : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ABlackHole();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	//Destroys the overlaping components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphereComponent;

	//Pulls components that are physically simulating towards the centre of the actor
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphereComponent;

	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		
};
