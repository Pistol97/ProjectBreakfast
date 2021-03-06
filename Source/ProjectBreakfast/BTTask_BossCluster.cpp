// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossCluster.h"
#include "BossAIController.h"
#include "BossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossCluster::UBTTask_BossCluster()
{
    NodeName = TEXT("Boss Cluster Attack");
}

EBTNodeResult::Type UBTTask_BossCluster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BossBlackboard = OwnerComp.GetBlackboardComponent();

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	ABossCharacter* boss = Cast<ABossCharacter>(AIOwner->GetCharacter());

	boss->ClusterAttack();

	BossBlackboard->SetValueAsInt("PrimaryCount", 0);

	return EBTNodeResult::Succeeded;
}
