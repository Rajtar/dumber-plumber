

#pragma once

#include "CoreMinimal.h"
#include "Pipe.h"
#include "PipePreview.generated.h"

/**
 * 
 */
UCLASS()
class DUMBERPLUMBER_API APipePreview : public APipe
{
	GENERATED_BODY()
public:
    
    APipePreview();

    void AdjustPipePreview();

    void ReleaseNeighbours();

    void UnlinkNeighbour(APipe* pipe) override;

    bool GetCanBeBuilt();

protected:

    virtual void BeginPlay() override;

    void LinkNeighbour(APipe* pipe) override;

private:

    void checkIfOverlaps();

    bool CanBeBuilt = true;

    TArray<APipe*> Neighbours;
};
