// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BossProjectile.h"
#include "BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Zinx.h"

#include <iostream>

// Sets default values
ABossCharacter::ABossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const ConstructorHelpers::FClassFinder<ABossAIController> bossAIController(TEXT
	("/Script/ProjectBreakfast.BossAIController"));

	AIControllerClass = bossAIController.Class;

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

		//�ִϸ��̼� ���
		bossAnimInstance->PlayPrimaryAttackMontage();

		//�÷��̾ ���� ����
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

		//�ִϸ��̼� ���
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

		//�ִϸ��̼� ���
		bossAnimInstance->PlayUltimateAttackMontage();
	}
	
	if (_bossBlackBoard->GetValueAsBool("SecondSequenceUlt"))
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
	if (_bossBlackBoard->GetValueAsBool("SecondSequenceUlt"))
	{
		_bossBlackBoard->SetValueAsBool("SecondSequenceUlt", false);
	}


	else
	{
		_bossBlackBoard->SetValueAsBool("FirstSequenceUlt", false);
		_bossBlackBoard->SetValueAsBool("SecondSequenceUlt", true);
	}
}

void ABossCharacter::BossDeath()
{
	if (bossAnimInstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Dead!"));

		//�ִϸ��̼� ���
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

	_bossBlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(GetOwner());

	_bossBlackBoard->SetValueAsBool("FirstSequenceUlt", true);
	_bossBlackBoard->SetValueAsBool("SecondSequenceUlt", false);
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
	}

	else
	{
		speed = 0.0f;
		//�÷��̾� ����
		bossAnimInstance->SetAimOffset();
	}



	_bossBlackBoard->SetValueAsFloat("BossHP", current_HP / max_HP * 100.0f);

	UE_LOG(LogTemp, Warning, TEXT("%f"), _bossBlackBoard->GetValueAsFloat("BossHP"));
}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

