


#include "PipeBuilt.h"
#include "Pipe.h"
#include "SourcePipe.h"
#include "TeamDestinationPipe.h"
#include "AssetStorage.h"
#include "Net/UnrealNetwork.h"


APipeBuilt::APipeBuilt() : Super()
{
	SetReplicates(true);
}

void APipeBuilt::BeginPlay()
{
	Super::BeginPlay();

	SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::NotConnected));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Build();
}

void APipeBuilt::Build()
{
	if (Role < ROLE_Authority)
	{
		ServerBuild();
		return;
	}

	FindNeighbourBuiltPipes(Neighbours);
	AdjustShapeAndRotationToNeighbours(Neighbours);

	std::vector<ASourcePipe*> sourcePipes;
	std::vector<ATeamDestinationPipe*> destinationPipes;
	std::vector<APipe*> chain;
	checkIfConnected(chain, sourcePipes, destinationPipes);

	if (!sourcePipes.empty() && !destinationPipes.empty())
	{
		setChainConnected(chain, sourcePipes, destinationPipes);
	}
}

void APipeBuilt::ServerBuild_Implementation()
{
	Build();
}

bool APipeBuilt::ServerBuild_Validate()
{
	return true;
}

void APipeBuilt::checkIfConnected(
	std::vector<APipe*>& chain,
	std::vector<ASourcePipe*>& sources,
	std::vector<ATeamDestinationPipe*>& destinations)
{
	for (const auto& neighbour : Neighbours)
	{
		if (neighbour == nullptr)
		{
			return;
		}
		if (auto source = Cast<ASourcePipe>(neighbour))
		{
			sources.emplace_back(source);
		}
		if (auto destination = Cast<ATeamDestinationPipe>(neighbour))
		{
			destinations.emplace_back(destination);
		}
		if (std::find(chain.begin(), chain.end(), neighbour) != chain.end())
		{
			return;
		}
		if (auto builtNeighbour = Cast<APipeBuilt>(neighbour))
		{
			chain.emplace_back(builtNeighbour);
			builtNeighbour->checkIfConnected(chain, sources, destinations);
		}
	}
}

void APipeBuilt::setChainConnected(
	const std::vector<APipe*>& chain,
	const std::vector<ASourcePipe*>& sources,
	const std::vector<ATeamDestinationPipe*>& destinations)
{
	for (auto pipe : chain)
	{
		pipe->SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Connected));
	}
	for (auto pipe : sources)
	{
		pipe->SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Connected));
	}
	for (auto pipe : destinations)
	{
		pipe->SetMaterial(*AssetStorage->PipeMaterials.Find(PipeState::Connected));
	}
}

void APipeBuilt::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APipeBuilt, Neighbours);
}

void APipeBuilt::LinkNeighbour(APipe* pipe)
{
	UE_LOG(LogTemp, Warning, TEXT("1 LinkNeighbour for %s number of neighbours: %d"), *this->GetName(), Neighbours.Num());
	Neighbours.Add(pipe);
	UE_LOG(LogTemp, Warning, TEXT("2 LinkNeighbour for %s number of neighbours: %d"), *this->GetName(), Neighbours.Num());
	AdjustShapeAndRotationToNeighbours(Neighbours);
}

void APipeBuilt::UnlinkNeighbour(APipe* pipe)
{
	Neighbours.Remove(pipe);
	AdjustShapeAndRotationToNeighbours(Neighbours);
}