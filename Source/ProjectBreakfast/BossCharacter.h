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

	void ClusterAttack();

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void FireCluster();

	void UltimateAttack();

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void FireLaserBeam();

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void NextSequence();

	void BossDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile, Meta = (AllowPrivateAccess = true))
		TSubclassOf<class ABossProjectile> projectile_Primary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile, Meta = (AllowPrivateAccess = true))
		TSubclassOf<class ABossProjectile> projectile_Cluster;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile, Meta = (AllowPrivateAccess = true))
		TSubclassOf<class AActor> ultimate_Laser;

private:
	class UBossAnimInstance* bossAnimInstance;
	class ABossAIController* bossAI;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Statistic, Meta = (AllowPrivateAccess = true))
		float current_HP;

	const float max_HP = 100.0f;
};
