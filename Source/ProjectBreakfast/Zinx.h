// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Zinx.generated.h"

class UDamageType;
class AGun;
class AStopWatch;

UCLASS()
class PROJECTBREAKFAST_API AZinx : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* spring_arm_;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* camera_;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack,
		Meta = (AllowPrivateAccess = true))
	bool is_attacking_;
	UPROPERTY()
	class UZinxAnimInstance* zinx_anim_;
	// Shooter Data Variable
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> gun_class_;
	UPROPERTY()
	AGun* gun_;	
	UPROPERTY(VisibleAnywhere, Category = "Shooting")
	TSubclassOf<UDamageType> damage_type;

public:
	// Sets default values for this character's properties
	AZinx();

	// Built-in Overriding Method
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Component Property 
	inline USpringArmComponent* GetSpringArm() const;
	inline UCameraComponent* GetCamera() const;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool is_interrupted);

	UFUNCTION(BlueprintCallable)
	void ForceGetBackToTheTime();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Input Feedback for Zinx
	void MoveForward(float input_value);
	void MoveHorizontal(float input_value);
	void Fire();
	void Skill();

	// Related to Zinx Adrenalin Skill Method
	void MakeTimeSlower(float adrenaline_time_rate);
	void EndSkill();
	void GetBackToTheTime();
	// Related to Zinx Adrenalin Skill Field
	FTimerHandle slow_handle_;
	AStopWatch* adrenalin_stop_watch_;
	AStopWatch* observer_stop_watch_;
	// Value: 0.0 <= TimeRate <= 1.0
	// 일반 시간 1초 = 1000ms
	const float kStandardTimeRate = 1.0f;
public:
	// 기획자야 일해라!
	// 아드레날린 타임 시간 효율: 1초 = 200ms
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	float kAdrenalinTimeRate = 0.2f;
	// 아드레날린 스킬 총 시간 몇초
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	float kAdrenalinMaxTime = 100.0f;
	// 기본 스킬 지속시간
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	float kDefaultSkillTime = 3.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	float left_time_ = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	bool is_adrenalin_on_ = false;
	// 스킬 초당 추가시간
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
	float skill_plus_value_ = 0.0f;

	// 징크스 이동속도 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Private)
	float speed = 0.0f;
private:
	float default_time_ = 3.0f;

	// Related to Projection
	FVector direction_to_move_;
	FRotator arm_rotation_to_;
	bool is_invoke_past_;
	const float arm_length_to_ = 100.0f;
	const float arm_length_speed_ = 3.0f;
	const float arm_rotation_speed_ = 10.0f;

	// Zinx Private Value
	const float kJumpMagnitude = 300.0f;

	//monster_set_stimulus
	class UAIPerceptionStimuliSourceComponent* stimulus;

	void setup_stimulus();

};

USpringArmComponent* AZinx::GetSpringArm() const
{
	return spring_arm_;
}

UCameraComponent* AZinx::GetCamera() const
{
	return camera_;
}