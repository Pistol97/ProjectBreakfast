// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StopWatch.generated.h"

UCLASS()
class PROJECTBREAKFAST_API AStopWatch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStopWatch();

	uint64 AccumulatedTime = 0;
	uint64 StartTime = 0;
	bool bIsStarted = false;

	void Start();
	void Stop();
	void Update();
	void Restart();
	void Reset();
	double GetAccumulatedTime() const;
	uint64 GetAccumulatedTimeMs() const;

	static double Cycles64ToSeconds(const uint64 Cycles64)
	{
		return static_cast<double>(Cycles64) * FPlatformTime::GetSecondsPerCycle64();
	}

	static uint64 Cycles64ToMilliseconds(const uint64 Cycles64)
	{
		const double Milliseconds = FMath::RoundToDouble(static_cast<double>(Cycles64 * 1000) * FPlatformTime::GetSecondsPerCycle64());
		return static_cast<uint64>(Milliseconds);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
