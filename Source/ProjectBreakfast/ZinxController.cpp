#include "ZinxController.h"

void AZinxController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly input_mode;
	SetInputMode(input_mode);
}