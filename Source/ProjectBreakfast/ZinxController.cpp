// Fill out your copyright notice in the Description page of Project Settings.


#include "ZinxController.h"

void AZinxController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly input_mode;
	SetInputMode(input_mode);
}