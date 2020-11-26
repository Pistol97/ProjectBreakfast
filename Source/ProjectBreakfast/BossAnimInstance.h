// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void PlayPrimaryAttackMontage();
	void PlayClusterAttackMontage();
	void PlayultimateAttackMontage();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "variable", meta = (AllowPrivateAccess = "true"))
		float speed;
	
};
