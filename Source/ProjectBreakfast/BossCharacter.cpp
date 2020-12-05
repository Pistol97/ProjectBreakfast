// Fill out your copyright notice in the Description page of Project Settings.
#include <iostream>

#include "BossCharacter.h"
#include "BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BossProjectile.h"

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

	auto Animinstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (Animinstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Primary Attack"));

		//애니메이션 재생
		Animinstance->PlayPrimaryAttackMontage();
		
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
	auto Animinstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (Animinstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Cluster Attack"));

		//애니메이션 재생
		Animinstance->PlayClusterAttackMontage();
	}
}

void ABossCharacter::FireCluster()
{
	FVector clusterPos = GetMesh()->GetSocketLocation("Muzzle_04");

	srand((unsigned int)time(0));

	for (int i = 0; i < 5; i++)
	{
		float randomFirePos = rand() % (95 + 1 - 15) + 15;

		//뒤로나가는 문제가 발생함
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

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

