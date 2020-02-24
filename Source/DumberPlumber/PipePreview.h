

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

protected:

    virtual void BeginPlay() override;

    void LinkNeighbour(APipe* pipe) override;

private:

    TArray<APipe*> Neighbours;
};
