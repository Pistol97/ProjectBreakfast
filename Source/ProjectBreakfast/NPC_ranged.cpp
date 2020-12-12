// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_ranged.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

#include "NPC_Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
//#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ANPC_ranged::ANPC_ranged()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
}

UAnimMontage* ANPC_ranged::get_montage() const
{
	return montage;
}

// Called when the game starts or when spawned
void ANPC_ranged::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANPC_ranged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPC_ranged::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANPC_ranged::range_attack()
{
	if (montage)
	{
		//애니메이션 재생
		PlayAnimMontage(montage);

		// 프로젝타일 발사를 시도합니다.
		if (ProjectileClass)
		{
            UWorld* World = GetWorld();
            if (World)
            {
                // 총구 위치에 발사체를 스폰시킵니다.
                ANPC_Projectile* Projectile = World->SpawnActor<ANPC_Projectile>(ProjectileClass, GetMesh()->GetSocketLocation("Muzzle_01"), GetMesh()->GetSocketRotation("Muzzle_01"));
                if (Projectile)
                {
                    // 발사 방향을 알아냅니다.
                    FVector LaunchDirection = GetMesh()->GetSocketRotation("Muzzle_01").Vector();
                    Projectile->FireInDirection(LaunchDirection);
                }
            }
		}
	}
}
