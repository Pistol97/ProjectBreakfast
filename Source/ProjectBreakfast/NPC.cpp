// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"

#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//npc 자연스러운 움직임
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

UAnimMontage* ANPC::get_montage() const
{
	return montage;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

APatrolPath* ANPC::get_patrol_path()
{
	return patrol_path;
}

void ANPC::melee_attack()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
}
