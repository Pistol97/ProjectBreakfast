// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZinxAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class PROJECTBREAKFAST_API UZinxAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn,
		Meta = (AllowPrivateAccess = true))
	float current_pawn_speed_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn,
		Meta = (AllowPrivateAccess = true))
	bool is_jump_;

public:
	UZinxAnimInstance();

public:
	virtual void NativeUpdateAnimation(float delta_seconds) override;

};
