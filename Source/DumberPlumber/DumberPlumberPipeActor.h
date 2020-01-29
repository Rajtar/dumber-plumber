#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DumberPlumberPipeActor.generated.h"

class ADumberPlumberCharacter;
class UCapsuleComponent;

UCLASS()
class DUMBERPLUMBER_API ADumberPlumberPipeActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ADumberPlumberPipeActor();

	void Interact(ACharacter * User) override;

	void MarkAsFocused() override;

	void UnmarkAsFocused() override;
	
	void DropPipe();

protected:
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Components")
	class ADumberPlumberCharacter* PlayerCharacter;

	virtual void BeginPlay() override;

private:
	void PickUpPipe(ACharacter* Character);
};
