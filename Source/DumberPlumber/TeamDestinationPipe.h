

#pragma once

#include "CoreMinimal.h"
#include "PipeBuilt.h"
#include "TeamDestinationPipe.generated.h"

/**
 * 
 */
UCLASS()
class DUMBERPLUMBER_API ATeamDestinationPipe : public APipeBuilt
{
	GENERATED_BODY()

public:

    ATeamDestinationPipe();

protected:

    void AdjustShapeAndRotationToNeighbours(const TArray<APipe*>& neighbours) final override;
};
