// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BossProjectile.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zinx.h"

#include <iostream>

// Sets default values
ABossCharacter::ABossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	current_HP = max_HP;

	speed = 0.0f;
}

void ABossCharacter::PrimaryAttack()
{
	FVector primaryPos = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator primaryRot = GetMesh()->GetSocketRotation("Muzzle_01");

	if (bossAnimInstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Primary Attack"));

		//애니메이션 재생
		bossAnimInstance->PlayPrimaryAttackMontage();

		//플레이어에 맞춰 조정
		primaryRot.Pitch -= 5.0f;
		primaryRot.Yaw -= 4.0f;

		ABossProjectile* projectile_primary = GetWorld()->SpawnActor<ABossProjectile>(projectile_Primary, primaryPos, primaryRot);

		if (projectile_primary)
		{
			UE_LOG(LogTemp, Warning, TEXT("Projectile in air"));
			projectile_primary->FireInDirection(primaryRot.Vector());
		}
	}
}

void ABossCharacter::ClusterAttack()
{
	if (bossAnimInstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Cluster Attack"));

		//애니메이션 재생
		bossAnimInstance->PlayClusterAttackMontage();
	}
}

void ABossCharacter::FireCluster()
{
	FVector clusterPos = GetMesh()->GetSocketLocation("Muzzle_04");

	for (int i = 0; i < 5; i++)
	{
		float randomFirePos = FMath::RandRange(-45, 45);

		FRotator clusterRot = GetActorForwardVector().Rotation();
		clusterRot += FRotator(50.0f, randomFirePos, 0.0f);

		ABossProjectile* projectile_cluster = GetWorld()->SpawnActor<ABossProjectile>(projectile_Cluster, clusterPos, clusterRot);

		if (projectile_cluster)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cluster in air"));
			projectile_cluster->FireInDirection(clusterRot.Vector());
		}
	}
}

void ABossCharacter::UltimateAttack()
{
	if (bossAnimInstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss First Ultimate Attack"));

		//애니메이션 재생
		bossAnimInstance->PlayUltimateAttackMontage();
	}

	if (bossAI->GetBlackboardComponent()->GetValueAsBool("SecondSequenceUlt"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Last Ultimate Attack"));
	}
}

void ABossCharacter::FireLaserBeam()
{
	FVector ultimatePos = GetMesh()->GetSocketLocation("Muzzle_04");
	FRotator ultimateRot = GetMesh()->GetForwardVector().Rotation();

	ultimateRot.Roll += 7;

	AActor* ultimate_laser1 = GetWorld()->SpawnActor<AActor>(ultimate_Laser, ultimatePos, ultimateRot);
	ultimate_laser1->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

	ultimateRot.Yaw += 90.0f;
	AActor* ultimate_laser2 = GetWorld()->SpawnActor<AActor>(ultimate_Laser, ultimatePos, ultimateRot);
	ultimate_laser2->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

	ultimateRot.Yaw += 180.0f;
	AActor* ultimate_laser3 = GetWorld()->SpawnActor<AActor>(ultimate_Laser, ultimatePos, ultimateRot);
	ultimate_laser3->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

	ultimateRot.Yaw += 270.0f;
	AActor* ultimate_laser4 = GetWorld()->SpawnActor<AActor>(ultimate_Laser, ultimatePos, ultimateRot);
	ultimate_laser4->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
}

void ABossCharacter::NextSequence()
{
	if (bossAI->GetBlackboardComponent()->GetValueAsBool("SecondSequenceUlt"))
	{
		bossAI->GetBlackboardComponent()->SetValueAsBool("SecondSequenceUlt", false);
	}


	else
	{
		bossAI->GetBlackboardComponent()->SetValueAsBool("FirstSequenceUlt", false);
		bossAI->GetBlackboardComponent()->SetValueAsBool("SecondSequenceUlt", true);
	}
}

void ABossCharacter::BossDeath()
{
	if (bossAnimInstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Dead!"));

		//애니메이션 재생
		bossAnimInstance->PlayDeathMontage();
	}

	if (bossAnimInstance->Montage_IsPlaying(bossAnimInstance->GetDeathMontage()))
	{

	}
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	bossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	bossAI = Cast<ABossAIController>(GetController());

	bossAI->GetBlackboardComponent()->SetValueAsBool("FirstSequenceUlt", true);
	bossAI->GetBlackboardComponent()->SetValueAsBool("SecondSequenceUlt", false);
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AZinx* zinx = Cast<AZinx>(PlayerPawn);
	if (bossAnimInstance->Montage_IsPlaying(bossAnimInstance->GetUltimateMontage()))
	{
		if (zinx->is_adrenalin_on_)
		{
			speed += 1.0f * zinx->kAdrenalinTimeRate;
		}

		else
		{
			speed += 1.0f;
		}

		FRotator rot = FRotator(0.0f, speed, 0.0f);
		SetActorRotation(rot);
		UE_LOG(LogTemp, Warning, TEXT("TEST"));
	}

	else
	{
		speed = 0.0f;
		//플레이어 조준
		bossAnimInstance->SetAimOffset();
	}



	bossAI->GetBlackboardComponent()->SetValueAsFloat("BossHP", current_HP / max_HP * 100.0f);

	UE_LOG(LogTemp, Warning, TEXT("%f"), bossAI->GetBlackboardComponent()->GetValueAsFloat("BossHP"));
}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

