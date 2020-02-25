

#pragma once

#include "CoreMinimal.h"
#include "Pipe.h"
#include <vector>
#include "PipeBuilt.generated.h"

/**
 * 
 */
UCLASS()
class DUMBERPLUMBER_API APipeBuilt : public APipe
{
	GENERATED_BODY()

public:

	APipeBuilt();

	void UnlinkNeighbour(APipe* pipe) override;

protected:

	void BeginPlay() override;

	void Build();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerBuild();

	void checkIfConnected(
		std::vector<APipe*>& chain,
		std::vector<class ASourcePipe*>& sources,
		std::vector<class ATeamDestinationPipe*>& destinations);

	void setChainConnected(
		const std::vector<APipe*>& chain,
		const std::vector<class ASourcePipe*>& sources,
		const std::vector<class ATeamDestinationPipe*>& destinations);

	void LinkNeighbour(APipe* pipe) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* BuildSound;

private:

	UPROPERTY(Replicated)
	TArray<APipe*> Neighbours;
	
};