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

	void DisplayPrompt(UCanvas * Canvas, ACharacter * User) override;
	
	void DropPipe() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleCollider;

	virtual void BeginPlay() override;

private:
	void PickUpPipe(ACharacter* character);

};
