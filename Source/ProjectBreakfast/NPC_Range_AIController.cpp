// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Range_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "GameFramework/Character.h"

ANPC_Range_AIController::ANPC_Range_AIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/NPC_Range_BT.NPC_Range_BT'"));
	if (obj.Succeeded())
	{
		btree_range = obj.Object;
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	setup_perception_system();
}

void ANPC_Range_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree_range);
	behavior_tree_component->StartTree(*btree_range);
}

void ANPC_Range_AIController::Tick(float DeltaSeconds)
{
	//월드 내의 플레이어 찾기
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//플레이어를 바라보도록
	SetFocus(PlayerPawn);
}

FRotator ANPC_Range_AIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}
	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void ANPC_Range_AIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree_range->BlackboardAsset);
	}
}

UBlackboardComponent* ANPC_Range_AIController::get_blackboard() const
{
	return blackboard;
}

void ANPC_Range_AIController::on_updated(TArray<AActor*> const& updated_actors)
{

}

void ANPC_Range_AIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	//APawn* playerpawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (auto const ch = Cast<AMyCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

void ANPC_Range_AIController::setup_perception_system()
{
	// 시각관련 객체 생성 & 초기화
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	sight_config->SightRadius = 1000.0f;//대상을 볼 수 있는 시거리
	sight_config->LoseSightRadius = sight_config->SightRadius;//이미 본 대상을 다시 볼 수 있는 시거리
	sight_config->PeripheralVisionAngleDegrees = 100.0f;//시야각
	sight_config->SetMaxAge(2.0f);//잊는데 걸리는 시간
	sight_config->AutoSuccessRangeFromLastSeenLocation = 1300.0f;//잊는데 필요한 거리
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	// 인식에 시각 요소 추가
	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_Range_AIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}