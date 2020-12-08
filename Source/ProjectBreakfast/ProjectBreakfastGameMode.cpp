// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBreakfastGameMode.h"
#include "UObject/ConstructorHelpers.h"

AProjectBreakfastGameMode::AProjectBreakfastGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT(
	"/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"
	));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
