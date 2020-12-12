#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root_ = CreateDefaultSubobject<USceneComponent>(TEXT(
		"ROOT"
	));
	SetRootComponent(root_);

	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT(
		"MESH"
	));
	mesh_->SetupAttachment(root_);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::PullTriggerEffect()
{
	UGameplayStatics::SpawnEmitterAttached(muzzle_flash_,
		mesh_, TEXT("MuzzleEffect"));
	UGameplayStatics::SpawnSoundAttached(muzzle_sound_, 
		mesh_, TEXT("MuzzleEffect"));

	APawn* owner_pawn = Cast<APawn>(GetOwner());
	if(owner_pawn == nullptr) return;
	AController* owner_controller = owner_pawn->GetController();
	if(owner_controller == nullptr) return;

	FVector location;
	FRotator rotation;
	owner_controller->GetPlayerViewPoint(location, rotation);

	FVector end = location + rotation.Vector() * max_range_;

	FHitResult hit;
	bool success = GetWorld()->LineTraceSingleByChannel(hit, location, end,
		ECollisionChannel::ECC_GameTraceChannel1);
	if (success)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), impact_sound_, hit.Location);

		FVector shot_direction = -rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impact_effect_
		, hit.Location, shot_direction.Rotation());
		FPointDamageEvent DamageEvent(damage_, hit, shot_direction, nullptr);
		AActor* hit_actor = hit.GetActor();
		if (hit_actor != nullptr)
		{
			hit_actor->TakeDamage(damage_, DamageEvent, owner_controller, 
				this);
		}
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

