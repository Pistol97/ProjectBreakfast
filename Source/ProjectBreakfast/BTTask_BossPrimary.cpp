// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossPrimary.h"
#include "BossAIController.h"
#include "BossCharacter.h"

UBTTask_BossPrimary::UBTTask_BossPrimary()
{
	NodeName = TEXT("Boss Primary Attack");
}

EBTNodeResult::Type UBTTask_BossPrimary::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	ABossCharacter* boss = Cast<ABossCharacter>(AIOwner->GetCharacter());

	boss->PrimaryAttack();

	return EBTNodeResult::Succeeded;
}