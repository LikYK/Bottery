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

	if (ScoreMaxSpawns.Contains(0.0f))
	{
		MaxSpawned = ScoreMaxSpawns[0.0f];
	}
}

// Called every frame
void AOrbSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrbSpawner::HandleScoreChanged(float NewScore)
{
	int32 TargetMaxSpawns = MaxSpawned;
	float CurrentScoreDifference = std::numeric_limits<float>::max();
	for (const TPair<float, int32>& Pair : ScoreMaxSpawns)
	{
		float ScoreDifference = NewScore - Pair.Key;
		if (NewScore >= Pair.Key && ScoreDifference < CurrentScoreDifference)
		{
			CurrentScoreDifference = ScoreDifference;
			TargetMaxSpawns = Pair.Value;
		}
	}
	MaxSpawned = TargetMaxSpawns;
}

