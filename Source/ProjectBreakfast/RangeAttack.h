// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NPC_ranged.h"
#include "RangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API URangeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	URangeAttack(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
private:
	bool montage_has_finished(ANPC_ranged* const npc);
	
};
