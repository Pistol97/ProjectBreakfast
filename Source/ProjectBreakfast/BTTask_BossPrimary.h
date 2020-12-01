// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BossPrimary.generated.h"

/**
 *
 */
UCLASS()
class PROJECTBREAKFAST_API UBTTask_BossPrimary : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_BossPrimary();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
