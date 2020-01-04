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
	
	virtual void Interact(ACharacter* User);
	virtual void MarkAsFocused();
	virtual void UnmarkAsFocused();
};
