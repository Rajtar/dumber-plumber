#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class ACharacter;
class UCanvas;
class AController;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to be implemented by interactable actors
 */
class DUMBERPLUMBER_API IInteractable
{
	GENERATED_BODY()

public:
	
	// This function will be called when the user uses the object
	virtual void Interact(ACharacter* User);
	
	// This function is called each frame from the hud, it should be used to put messages to the screen, like the USE prompt in UDK
	virtual void DisplayPrompt(UCanvas* Canvas, ACharacter* User);
};
