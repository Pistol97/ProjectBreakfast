// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NPC_AIController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// AI controller , NPC 불러오기
	auto const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner());
	auto const npc = cont->GetPawn();

	// 원점 위치로 사용할 npc 위치 구함
	FVector const origin = npc->GetActorLocation();

	// 네비게이션 시스템을 가져와 NavMesh에 랜덤 위치 생성
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation loc;

	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
	{
		cont->get_blackboard()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
	}

	// 성공
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}