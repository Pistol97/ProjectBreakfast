// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPathPoint.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "blackboard_keys.h"

UFindPatrolPathPoint::UFindPatrolPathPoint(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Patrol Path Point");
}

EBTNodeResult::Type UFindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// AI controller ��������
	ANPC_AIController* const controller = Cast<ANPC_AIController>(owner_comp.GetAIOwner());

	// �������� ��� �ε��� ��������
	int const index = controller->get_blackboard()->GetValueAsInt(bb_keys::patrol_path_index);

	// ��� ��������
	ANPC* const npc = Cast<ANPC>(controller->GetPawn());
	FVector const point = npc->get_patrol_path()->get_patrol_point(index);

	// global position���� �ٲٱ�
	FVector const global_point = npc->get_patrol_path()->GetActorTransform().TransformPosition(point);

	// ��θ� �����忡 ����
	controller->get_blackboard()->SetValueAsVector(bb_keys::patrol_path_vector, global_point);

	// ����
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}