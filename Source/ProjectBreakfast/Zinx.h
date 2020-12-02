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

public:
	// Sets default values for this character's properties
	AZinx();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	inline USpringArmComponent* GetSpringArm() const;
	inline UCameraComponent* GetCamera() const;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Input Feedback for Zinx Transform
	void MoveVertical(float input_value);
	void MoveHorizontal(float input_value);
	void RotatePitch(float input_value);
	void RotateYaw(float input_value);

	// Input Feedback for Game's View Space
	void ViewChange();

private:
	FVector direction_to_move_;
	FRotator arm_rotation_to_;

	bool is_invoke_past_;
	float arm_length_to_;
	float arm_length_speed_;
	float arm_rotation_speed_;
};

USpringArmComponent* AZinx::GetSpringArm() const
{
	return spring_arm_;
}

UCameraComponent* AZinx::GetCamera() const
{
	return camera_;
}