// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPC_Range_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBREAKFAST_API ANPC_Range_AIController : public AAIController
{
	GENERATED_BODY()
public:
	ANPC_Range_AIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	class UBlackboardComponent* get_blackboard() const;

	virtual void Tick(float DeltaSeconds);

	virtual FRotator GetControlRotation() const override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree_range;

	class UBlackboardComponent* blackboard;

	class UAISenseConfig_Sight* sight_config;

	UFUNCTION()
		void on_updated(TArray<AActor*> const& updated_actors);

	UFUNCTION()
		void on_target_detected(AActor* actor, FAIStimulus const stimulus);

	void setup_perception_system();
};
