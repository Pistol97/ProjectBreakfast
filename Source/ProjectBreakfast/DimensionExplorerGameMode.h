#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DimensionExplorerGameMode.generated.h"

UCLASS()
class PROJECTBREAKFAST_API ADimensionExplorerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADimensionExplorerGameMode();

	virtual void PostLogin(APlayerController* new_player) override;
};
