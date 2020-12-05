// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Zinx.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Input Feedback for Zinx
	void MoveForward(float input_value);
	void MoveHorizontal(float input_value);
	void RotatePitch(float input_value);
	void RotateYaw(float input_value);
	void Fire();

	// Related to Projection
	FVector direction_to_move_;
	FRotator arm_rotation_to_;
	bool is_invoke_past_;
	const float arm_length_to_ = 100.0f;
	const float arm_length_speed_ = 3.0f;
	const float arm_rotation_speed_ = 10.0f;

	// Zinx Private Value
	const float kJumpMagnitude = 300.0f;

};

USpringArmComponent* AZinx::GetSpringArm() const
{
	return spring_arm_;
}

UCameraComponent* AZinx::GetCamera() const
{
	return camera_;
}