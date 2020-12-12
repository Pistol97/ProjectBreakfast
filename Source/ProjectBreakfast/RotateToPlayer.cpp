// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateToPlayer.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"

URotateToPlayer::URotateToPlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Rotate to Player");
}

EBTNodeResult::Type URotateToPlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// get NPC
	AAIController* const cont = owner_comp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (ANPC_ranged* const npc = Cast<ANPC_ranged>(cont->GetPawn()))
	{
		//FRotator NewRotation = PlayerPawn->GetActorRotation();
		//NewRotation.Yaw += 180.f;

		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(npc->GetActorLocation(), PlayerPawn->GetActorLocation());
		
		npc->SetActorRelativeRotation(PlayerRot);
	}

	if (!bb_keys::player_is_in_range_range)
	{
		ANPC_ranged* npc = Cast<ANPC_ranged>(cont->GetPawn());
		npc->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}