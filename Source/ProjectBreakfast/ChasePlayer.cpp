// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// ai controller로 블랙보드에서 target location 가져오기
	ANPC_AIController* const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner());
	FVector const player_location = cont->get_blackboard()->GetValueAsVector(GetSelectedBlackboardKey());

	// 플레이어 위치로 이동
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location);

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//FRotator NewRotation = PlayerPawn->GetActorRotation();
	//NewRotation.Yaw += 180.f;
	//cont->SetActorRelativeRotation(NewRotation);

	// 성공
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
