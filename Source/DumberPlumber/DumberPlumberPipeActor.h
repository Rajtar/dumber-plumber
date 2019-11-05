// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DumberPlumberPipeActor.generated.h"

class UCapsuleComponent;

UCLASS()
class DUMBERPLUMBER_API ADumberPlumberPipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADumberPlumberPipeActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* Capsule;

	virtual void BeginPlay() override;

public:	
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
