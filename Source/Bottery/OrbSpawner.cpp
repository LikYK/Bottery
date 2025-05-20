// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbSpawner.h"
#include "BotteryGameState.h"


// Sets default values
AOrbSpawner::AOrbSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOrbSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (ABotteryGameState* GS = GetWorld()->GetGameState<ABotteryGameState>())
	{
		GS->OnScoreUpdated.AddUniqueDynamic(this, &AOrbSpawner::HandleScoreChanged);
	}

	if (SpawnInfos.Contains(0.0f))
	{
		SetSpawnInfo(SpawnInfos[0.0f]);
	}
	else
	{
		CurrentSpawnInfo.SpawnTable = SpawnTable;
		CurrentSpawnInfo.SpawnAmount = SpawnAmount;
		CurrentSpawnInfo.SpawnInterval = SpawnInterval;
		CurrentSpawnInfo.MaxSpawned = MaxSpawned;
	}
}

// Called every frame
void AOrbSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrbSpawner::SetSpawnInfo(FOrbSpawnInfo SpawnInfo)
{
	CurrentSpawnInfo = SpawnInfo;

	SpawnTable = CurrentSpawnInfo.SpawnTable;
	SpawnAmount = CurrentSpawnInfo.SpawnAmount;
	SpawnInterval = CurrentSpawnInfo.SpawnInterval;
	MaxSpawned = CurrentSpawnInfo.MaxSpawned;
}

void AOrbSpawner::HandleScoreChanged(float NewScore)
{
	FOrbSpawnInfo TargetSpawnInfo = CurrentSpawnInfo;
	float CurrentScoreDifference = std::numeric_limits<float>::max();
	for (const TPair<float, FOrbSpawnInfo>& Pair : SpawnInfos)
	{
		float ScoreDifference = NewScore - Pair.Key;
		// Find the Pair in the map with key closest to current score that is smaller than current score
		if (NewScore >= Pair.Key && ScoreDifference < CurrentScoreDifference)
		{
			CurrentScoreDifference = ScoreDifference;
			TargetSpawnInfo = Pair.Value;
		}
	}
	SetSpawnInfo(TargetSpawnInfo);
}

