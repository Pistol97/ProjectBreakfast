// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
ANPC_Projectile::ANPC_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ü�� �ܼ� �ݸ��� ǥ������ ����մϴ�.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ANPC_Projectile::OnHit);

	// ��ü�� �ݸ��� �ݰ��� �����մϴ�.
	CollisionComponent->InitSphereRadius(15.0f);
	// ��Ʈ ������Ʈ�� �ݸ��� ������Ʈ�� �����մϴ�.
	RootComponent = CollisionComponent;

	// ProjectileMovementComponent �� ����Ͽ� �� �߻�ü�� ��� �����մϴ�.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// 3 �� �� �׽��ϴ�.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ANPC_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ������Ÿ���� �ӵ��� �߻� �������� �ʱ�ȭ��Ű�� �Լ��Դϴ�.
void ANPC_Projectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// ������Ÿ�Ͽ� ���� ������ ȣ��Ǵ� �Լ��Դϴ�.
void ANPC_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
		UE_LOG(LogTemp, Log, TEXT("!!!!!!!!!!!ONHIT!!!!!!!!!!"));
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{

		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}