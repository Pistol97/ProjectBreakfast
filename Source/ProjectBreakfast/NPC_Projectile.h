// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_Projectile.generated.h"

UCLASS()
class PROJECTBREAKFAST_API ANPC_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 구체 콜리전 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComponent;

	// 프로젝타일 무브먼트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovementComponent;

	// 발사체의 속도를 발사 방향으로 초기화시킵니다.
	void FireInDirection(const FVector& ShootDirection);

	// 프로젝타일이 무언가에 맞으면 호출되는 함수입니다.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
