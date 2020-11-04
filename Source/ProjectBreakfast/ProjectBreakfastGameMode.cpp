// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBreakfastGameMode.h"
#include "ProjectBreakfastHUD.h"
#include "ProjectBreakfastCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectBreakfastGameMode::AProjectBreakfastGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectBreakfastHUD::StaticClass();
}
