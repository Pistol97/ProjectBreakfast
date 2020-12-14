// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "NPC_HealthBar.h"



// Sets default values
ANPC::ANPC() : health(max_health), widget_component(CreateDefaultSubobject<UWidgetComponent>(TEXT("NPC_HealthBar")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//npc 자연스러운 움직임
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

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

	widget_component->SetActive(false);
}

UAnimMontage* ANPC::get_montage() const
{
	return montage;
}

float ANPC::get_health() const
{
	return health;
}

float ANPC::get_max_health() const
{
	return max_health;
}

void ANPC::set_health(float const new_health)
{
	health = new_health;
	if (health <= 0)
	{
		PlayAnimMontage(death_montage);
		UE_LOG(LogTemp, Warning, TEXT("npc died"));
	}
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

	auto const uw = Cast<UNPC_HealthBar>(widget_component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent(health / max_health);
	}

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
