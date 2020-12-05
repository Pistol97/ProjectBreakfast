// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAnimInstance.h"

UBossAnimInstance::UBossAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PRIMARY_MONTAGE(TEXT
	("/Game/Boss/Animation/Primary_Montage.Primary_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> CLUSTER_MONTAGE(TEXT
	("/Game/Boss/Animation/Cluster_Montage.Cluster_Montage"));

	if (PRIMARY_MONTAGE.Succeeded())
	{
		primary_Attack = PRIMARY_MONTAGE.Object;
	}

	if (CLUSTER_MONTAGE.Succeeded())
	{
		cluster_Attack = CLUSTER_MONTAGE.Object;
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
