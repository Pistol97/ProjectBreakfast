// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInRangeRange.h"
#include "NPC_Range_AIController.h"
#include "NPC_ranged.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include <cmath>

UIsPlayerInRangeRange::UIsPlayerInRangeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Range Range");
}

void UIsPlayerInRangeRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	// get NPC
	ANPC_Range_AIController* const cont = Cast<ANPC_Range_AIController>(owner_comp.GetAIOwner());
	ANPC_ranged* const npc = Cast<ANPC_ranged>(cont->GetPawn());

	// get player character
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//
	float const distance = npc->GetDistanceTo(player);
	//
	UE_LOG(LogTemp, Warning, TEXT("Distance: %d"), distance);

	// 플레이어와의 거리가 가까우면 참 아니면 거짓 반환
	cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_range_range, 
		(npc->GetDistanceTo(player) < range_range_large)&&
		(npc->GetDistanceTo(player) > range_range_small));
}