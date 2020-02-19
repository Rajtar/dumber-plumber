

#pragma once

#include "CoreMinimal.h"
#include "Pipe.h"
#include "TeamDestinationPipe.generated.h"

/**
 * 
 */
UCLASS()
class DUMBERPLUMBER_API ATeamDestinationPipe : public APipe
{
	GENERATED_BODY()

public:

    ATeamDestinationPipe();

protected:

    void AdjustShapeAndRotationToNeighbours() final override;
};
