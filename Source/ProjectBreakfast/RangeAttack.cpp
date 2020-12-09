// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeAttack.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

URangeAttack::URangeAttack(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Range Attack");
}

EBTNodeResult::Type URangeAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// get NPC
	AAIController* const cont = owner_comp.GetAIOwner();

	if (ANPC_ranged* const npc = Cast<ANPC_ranged>(cont->GetPawn()))
	{
		if (montage_has_finished(npc))
		{
			npc->range_attack();
		}
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool URangeAttack::montage_has_finished(ANPC_ranged* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->get_montage());
}

