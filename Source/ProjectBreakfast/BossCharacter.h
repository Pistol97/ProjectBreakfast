// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossCharacter.generated.h"

UCLASS()
class PROJECTBREAKFAST_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossCharacter();

	void PrimaryAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite, Category = Muzzle, Meta = (AllowPrivateAccess = true))
		UParticleSystem* muzzle_Primary;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile, Meta = (AllowPrivateAccess = true))
		TSubclassOf<class ABossProjectile> projectile_Primary;


};
