// Fill out your copyright notice in the Description page of Project Settings.


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
	UE_LOG(LogTemp, Warning, TEXT("Boss Primary Attack"));

	auto Animinstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (Animinstance != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Success Fire Primary Attack"));

		//애니메이션 재생
		Animinstance->PlayPrimaryAttackMontage();

		//총구 앞 소켓에서 파티클 재생
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), muzzle_Primary, GetMesh()->GetSocketLocation("Muzzle_01"));
		
		ABossProjectile* projectile_primary = GetWorld()->SpawnActor<ABossProjectile>(projectile_Primary, GetMesh()->GetSocketLocation("Muzzle_01"), GetMesh()->GetSocketRotation("Muzzle_01"));
		
		if (projectile_primary)
		{
			UE_LOG(LogTemp, Warning, TEXT("Projectile in air"));
			FVector direction = GetMesh()->GetSocketRotation("Muzzle_01").Vector();
			projectile_primary->FireInDirection(direction);
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

