

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssetStorage.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class PipeType : uint8
{
	Straight,
	Curve,
	T_Like,
	Cross
};

UENUM(BlueprintType)
enum class PipeState : uint8
{
	Connected,
	NotConnected,
	Preview
};

UCLASS(Blueprintable, BlueprintType)
class DUMBERPLUMBER_API UAssetStorage : public UObject
{
	GENERATED_BODY()
	
public:
	UAssetStorage(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Assets")
	TMap<PipeType, class UStaticMesh*> PipeMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipe Assets")
	TMap<PipeState, class UMaterial*> PipeMaterials;
};
