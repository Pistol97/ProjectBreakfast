// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NPC_ranged.h"
#include "RotateToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API URotateToPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	URotateToPlayer(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
