// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ABossAIController::BeginPlay()
{
    Super::BeginPlay();
    
    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
    }
}

void ABossAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    //월드 내의 플레이어 찾기
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    //플레이어 위치 업데이트
    GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    GetBlackboardComponent()->SetValueAsVector(TEXT("LastPlayerLocation"), PlayerPawn->GetActorLocation());
}