// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyCharacter.h"

#include "Perception/AISenseConfig_Sight.h"
//#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "GameFramework/Character.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/NPC_BT.NPC_BT'"));
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	setup_perception_system();
}

void ANPC_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}

void ANPC_AIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

UBlackboardComponent* ANPC_AIController::get_blackboard() const
{
	return blackboard;
}

void ANPC_AIController::on_updated(TArray<AActor*> const& updated_actors)
{
	
}

void ANPC_AIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	//APawn* playerpawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (auto const ch = Cast<AMyCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

void ANPC_AIController::setup_perception_system()
{
	// �ð����� ��ü ���� & �ʱ�ȭ
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	sight_config->SightRadius = 500.0f;//����� �� �� �ִ� �ðŸ�
	sight_config->LoseSightRadius = sight_config->SightRadius;//�̹� �� ����� �ٽ� �� �� �ִ� �ðŸ�
	sight_config->PeripheralVisionAngleDegrees = 90.0f;//�þ߰�
	sight_config->SetMaxAge(2.0f);//�شµ� �ɸ��� �ð�
	sight_config->AutoSuccessRangeFromLastSeenLocation = 600.0f;//�شµ� �ʿ��� �Ÿ�
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;
	
	// �νĿ� �ð� ��� �߰�
	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_AIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}