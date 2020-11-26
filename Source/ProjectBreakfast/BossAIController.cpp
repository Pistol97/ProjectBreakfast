// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"

#include "Kismet/GameplayStatics.h"

void ABossAIController::BeginPlay()
{
    Super::BeginPlay();
    
}

void ABossAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    //월드 내의 플레이어 찾기
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    //플레이어를 바라보도록
    SetFocus(PlayerPawn);

    //플레이어를 향해 이동
    MoveToActor(PlayerPawn, playerAcceptanceDistance);
}