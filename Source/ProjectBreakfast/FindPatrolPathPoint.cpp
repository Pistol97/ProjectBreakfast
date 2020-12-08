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
	// AI controller 가져오기
	ANPC_AIController* const controller = Cast<ANPC_AIController>(owner_comp.GetAIOwner());

	// 블랙보드의 경로 인덱스 가져오기
	int const index = controller->get_blackboard()->GetValueAsInt(bb_keys::patrol_path_index);

	// 경로 가져오기
	ANPC* const npc = Cast<ANPC>(controller->GetPawn());
	FVector const point = npc->get_patrol_path()->get_patrol_point(index);

	// global position으로 바꾸기
	FVector const global_point = npc->get_patrol_path()->GetActorTransform().TransformPosition(point);

	// 경로를 블랙보드에 저장
	controller->get_blackboard()->SetValueAsVector(bb_keys::patrol_path_vector, global_point);

	// 성공
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}