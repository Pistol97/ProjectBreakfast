// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BossDeath.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API UBTTask_BossDeath : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_BossDeath();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
