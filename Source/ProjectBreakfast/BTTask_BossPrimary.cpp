// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossPrimary.h"
#include "BossAIController.h"
#include "BossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossPrimary::UBTTask_BossPrimary()
{
	NodeName = TEXT("Boss Primary Attack");
}

EBTNodeResult::Type UBTTask_BossPrimary::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BossBlackboard = OwnerComp.GetBlackboardComponent();

	int count = BossBlackboard->GetValueAsInt("PrimaryCount");

	count++;

	UE_LOG(LogTemp, Warning, TEXT("Attack Count :: %d"), count);

	BossBlackboard->SetValueAsInt("PrimaryCount", count);

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	ABossCharacter* boss = Cast<ABossCharacter>(AIOwner->GetCharacter());

	boss->PrimaryAttack();

	return EBTNodeResult::Succeeded;
}