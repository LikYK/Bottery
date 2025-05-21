// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/OrbSpawner.h"
#include "UEFramework/BotteryGameState.h"


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
	
	// Listen to score change to update spawn info
	if (ABotteryGameState* GS = GetWorld()->GetGameState<ABotteryGameState>())
	{
		GS->OnScoreUpdated.AddUniqueDynamic(this, &AOrbSpawner::HandleScoreChanged);
	}

	// If there is a spawn info for score 0, apply it
	if (SpawnInfos.Contains(0.0f))
	{
		SetSpawnInfo(SpawnInfos[0.0f]);
	}
	else
	{
		// Else fallback to the spawn info in this spawner (copy values into CurrentSpawnInfo so they can be used in HandleScoreChanged)
		CurrentSpawnInfo.SpawnTableDataAsset = SpawnTableDataAsset;
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
	// Update the SpawnInfo property/data member first (it is used in HandleScoreChanged)
	CurrentSpawnInfo = SpawnInfo;

	// And use it to update the actual spawn info and apply
	SpawnTableDataAsset = CurrentSpawnInfo.SpawnTableDataAsset;
	SpawnAmount = CurrentSpawnInfo.SpawnAmount;
	SpawnInterval = CurrentSpawnInfo.SpawnInterval;
	MaxSpawned = CurrentSpawnInfo.MaxSpawned;
	UpdateSpawner(); // Call this function to apply the changes
}

void AOrbSpawner::HandleScoreChanged(float NewScore)
{
	FOrbSpawnInfo TargetSpawnInfo = CurrentSpawnInfo; // Fallback to the current spawn info if none is found
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

