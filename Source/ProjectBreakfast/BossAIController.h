// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABossAIController();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	class UBehaviorTree* AIBehavior;
};
