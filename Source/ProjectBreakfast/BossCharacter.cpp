// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BossProjectile.h"

#include <iostream>

// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	//auto Animinstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
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

	srand((unsigned int)time(0));

	for (int i = 0; i < 5; i++)
	{
		float randomFirePos = rand() % (95 + 1 - 15) + 15;

		//�ڷγ����� ������ �߻���
		randomFirePos += 180.0f;

		FRotator clusterRot = GetMesh()->GetSocketRotation("Muzzle_04");
		clusterRot = FRotator(clusterRot.Pitch, clusterRot.Yaw + randomFirePos, clusterRot.Roll);

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
	//auto Animinstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (bossAnimInstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Play Boss Ultimate Attack"));

		//�ִϸ��̼� ���
		bossAnimInstance->PlayUltimateAttackMontage();
	}
}

void ABossCharacter::FireLaserBeam()
{	
	FVector ultimatePos = GetMesh()->GetSocketLocation("Muzzle_04");
	FRotator ultimateRot = GetMesh()->GetForwardVector().Rotation();

	AActor* ultimate_laser = GetWorld()->SpawnActor<AActor>(ultimate_Laser, ultimatePos, ultimateRot);
	//ultimate_laser->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "Muzzle_04");
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	bossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//FRotator origin = GetActorRotation();

	//������ ���ݽ�
	if (bossAnimInstance->Montage_IsPlaying(bossAnimInstance->GetUltimateMontage()))
	{
		FRotator adj = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
		FRotator rot = FRotator(adj.Roll, adj.Yaw - 90, 0);

		//�÷��̾� ����
		GetMesh()->SetWorldRotation(rot);
	}

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

