// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DumberPlumberGameMode.h"
#include "DumberPlumberHUD.h"
#include "DumberPlumberCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADumberPlumberGameMode::ADumberPlumberGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADumberPlumberHUD::StaticClass();
}

ETeamEnum ADumberPlumberGameMode::ChooseTeam(ADumberPlumberCharacter* character)
{
	if (redPlayers >= bluePlayers)
	{
		bluePlayers++;
		return ETeamEnum::BLUE;
	}
	redPlayers++;
	return ETeamEnum::RED;
}
