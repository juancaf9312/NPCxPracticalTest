// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NPCxPracticalTestGameMode.h"
#include "NPCxPracticalTestHUD.h"
#include "NPCxPracticalTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANPCxPracticalTestGameMode::ANPCxPracticalTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANPCxPracticalTestHUD::StaticClass();
}
