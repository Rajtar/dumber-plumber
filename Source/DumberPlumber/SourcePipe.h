

#pragma once

#include "CoreMinimal.h"
#include "PipeBuilt.h"
#include "SourcePipe.generated.h"

/**
 * 
 */
UCLASS()
class DUMBERPLUMBER_API ASourcePipe : public APipeBuilt
{
	GENERATED_BODY()

public:
	ASourcePipe();
	
protected:

	void AdjustShapeAndRotationToNeighbours(const TArray<APipe*>& neighbours) final override;
};
