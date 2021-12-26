// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAnimInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "BossCharacter.h"

UBossAnimInstance::UBossAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PRIMARY_MONTAGE(TEXT
	("/Game/Boss/Animation/Primary_Montage.Primary_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CLUSTER_MONTAGE(TEXT
	("/Game/Boss/Animation/Cluster_Montage.Cluster_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ULTIMATE_MONTAGE(TEXT
	("/Game/Boss/Animation/Ultimate_Montage.Ultimate_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT
	("/Game/Boss/Animation/Boss_Death.Boss_Death"));

	if (PRIMARY_MONTAGE.Succeeded())
	{
		primary_Attack = PRIMARY_MONTAGE.Object;
	}

	if (CLUSTER_MONTAGE.Succeeded())
	{
		cluster_Attack = CLUSTER_MONTAGE.Object;
	}

	if (ULTIMATE_MONTAGE.Succeeded())
	{
		ultimate_Attack = ULTIMATE_MONTAGE.Object;
	}

	if (DEATH_MONTAGE.Succeeded())
	{
		boss_death = DEATH_MONTAGE.Object;
	}
}

void UBossAnimInstance::PlayPrimaryAttackMontage()
{
	if (!Montage_IsPlaying(primary_Attack))
	{
		Montage_Play(primary_Attack, 1.0f);
	}
}

void UBossAnimInstance::PlayClusterAttackMontage()
{
	if (!Montage_IsPlaying(cluster_Attack))
	{
		Montage_Play(cluster_Attack, 1.0f);
	}
}

void UBossAnimInstance::PlayUltimateAttackMontage()
{
	if (!Montage_IsPlaying(ultimate_Attack))
	{
		Montage_Play(ultimate_Attack, 1.0f);
	}
}

void UBossAnimInstance::PlayDeathMontage()
{
	if (!Montage_IsPlaying(boss_death))
	{
		Montage_Play(boss_death, 1.0f);
	}
}

void UBossAnimInstance::SetAimOffset()
{	
	FVector playerPos = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();

	FRotator rot = UKismetMathLibrary::FindLookAtRotation(TryGetPawnOwner()->GetActorLocation(), playerPos);

	TryGetPawnOwner()->GetRootComponent()->SetWorldRotation(rot);
}