// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAnimInstance.h"

UBossAnimInstance::UBossAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PRIMARY_MONTAGE(TEXT
	("/Game/Boss/Characters/Heroes/GRIM/Animations/Primary_Montage.Primary_Montage"));

	if (PRIMARY_MONTAGE.Succeeded())
	{
		primary_Attack = PRIMARY_MONTAGE.Object;
	}
}

void UBossAnimInstance::PlayPrimaryAttackMontage()
{
	if (!Montage_IsPlaying(primary_Attack))
	{
		Montage_Play(primary_Attack, 1.0f);
	}
}