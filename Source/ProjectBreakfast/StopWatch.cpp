#include "StopWatch.h"
#include "HAL/PlatformTime.h"

// Sets default values
AStopWatch::AStopWatch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStopWatch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStopWatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStopWatch::Start()
{
	if (!bIsStarted)
	{
		bIsStarted = true;
		StartTime = FPlatformTime::Cycles64();
	}
}

void AStopWatch:: Stop()
{
	if (bIsStarted)
	{
		bIsStarted = false;
		AccumulatedTime += FPlatformTime::Cycles64() - StartTime;
	}
}

void AStopWatch::Update()
{
	if (bIsStarted)
	{
		uint64 CrtTime = FPlatformTime::Cycles64();
		AccumulatedTime += CrtTime - StartTime;
		StartTime = CrtTime;
	}
}

void AStopWatch::Restart()
{
	AccumulatedTime = 0;
	bIsStarted = true;
	StartTime = FPlatformTime::Cycles64();
}

void AStopWatch::Reset()
{
	AccumulatedTime = 0;
	StartTime = 0;
	bIsStarted = false;
}

double AStopWatch::GetAccumulatedTime() const
{
	return AStopWatch::Cycles64ToSeconds(AccumulatedTime);
}

uint64 AStopWatch::GetAccumulatedTimeMs() const
{
	return AStopWatch::Cycles64ToMilliseconds(AccumulatedTime);
}