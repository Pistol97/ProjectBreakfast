// Fill out your copyright notice in the Description page of Project Settings.


#include "DimensionExplorerGameMode.h"
#include "Zinx.h"
#include "ZinxController.h"

ADimensionExplorerGameMode::ADimensionExplorerGameMode()
{
	DefaultPawnClass = AZinx::StaticClass();
	PlayerControllerClass = AZinxController::StaticClass();
}

void ADimensionExplorerGameMode::PostLogin(APlayerController* new_player)
{
	Super::PostLogin(new_player);
}