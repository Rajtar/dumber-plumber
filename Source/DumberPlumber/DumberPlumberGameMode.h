// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TeamEnum.h"

#include "DumberPlumberGameMode.generated.h"

UCLASS(minimalapi)
class ADumberPlumberGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADumberPlumberGameMode();

	UFUNCTION()
	ETeamEnum ChooseTeam(class ADumberPlumberCharacter* character);

private:

	UPROPERTY()
	int redPlayers;

	UPROPERTY()
	int bluePlayers;

protected:

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> BlueSpawPoints;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> RedSpawPoints;
};