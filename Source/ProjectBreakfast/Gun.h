// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class PROJECTBREAKFAST_API AGun : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* root_;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh_;
	UPROPERTY(EditAnywhere)
	UParticleSystem* muzzle_flash_;
	UPROPERTY(EditAnywhere)
	UParticleSystem* impact_effect_;
	UPROPERTY(EditAnywhere)
	USoundBase* muzzle_sound_;
	UPROPERTY(EditAnywhere)
	USoundBase* impact_sound_;
	UPROPERTY(EditAnywhere)
	float max_range_ = 10000.0f;
	UPROPERTY(EditAnywhere)
	float damage_ = 10.0f;

public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTriggerEffect();

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
