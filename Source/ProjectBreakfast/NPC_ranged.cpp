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

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "NPC_HealthBar.h"

// Sets default values
ANPC_ranged::ANPC_ranged() : health(max_health), widget_component(CreateDefaultSubobject<UWidgetComponent>(TEXT("NPC_HealthBar")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	if (widget_component)
	{
		widget_component->SetupAttachment(RootComponent);
		widget_component->SetWidgetSpace(EWidgetSpace::Screen);
		widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Game/AI/NPC_HealthBar_BP"));
		if (widget_class.Succeeded())
		{
			widget_component->SetWidgetClass(widget_class.Class);
		}
	}
}

UAnimMontage* ANPC_ranged::get_montage() const
{
	return montage;
}

float ANPC_ranged::get_health() const
{
	return health;
}

float ANPC_ranged::get_max_health() const
{
	return max_health;
}

void ANPC_ranged::set_health(float const new_health)
{
	health = new_health;
	if (health <= 0)
	{
		PlayAnimMontage(death_montage);
		UE_LOG(LogTemp, Warning, TEXT("npc died"));
	}
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

	auto const uw = Cast<UNPC_HealthBar>(widget_component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent(health / max_health);
	}
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
