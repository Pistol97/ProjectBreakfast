// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossUltimate.h"
#include "BossAIController.h"
#include "BossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossUltimate::UBTTask_BossUltimate()
{
	NodeName = TEXT("Boss Ultimate Attack");
}

EBTNodeResult::Type UBTTask_BossUltimate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BossBlackboard = OwnerComp.GetBlackboardComponent();

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	ABossCharacter* boss = Cast<ABossCharacter>(AIOwner->GetCharacter());

	boss->UltimateAttack();

	return EBTNodeResult::Succeeded;
}
