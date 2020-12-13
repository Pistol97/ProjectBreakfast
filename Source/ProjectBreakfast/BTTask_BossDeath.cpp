// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossDeath.h"
#include "BossAIController.h"
#include "BossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossDeath::UBTTask_BossDeath()
{
	NodeName = TEXT("Boss Death");
}

EBTNodeResult::Type UBTTask_BossDeath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BossBlackboard = OwnerComp.GetBlackboardComponent();

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	ABossCharacter* boss = Cast<ABossCharacter>(AIOwner->GetCharacter());

	boss->BossDeath();

	return EBTNodeResult::Succeeded;
}
