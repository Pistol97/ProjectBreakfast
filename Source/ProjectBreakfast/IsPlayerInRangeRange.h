// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInRangeRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API UIsPlayerInRangeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UIsPlayerInRangeRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float range_range_large = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float range_range_small = 400.0f;
};
