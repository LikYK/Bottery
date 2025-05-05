// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AOrbSpawner::AOrbSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
}

// Called when the game starts or when spawned
void AOrbSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TotalWeight = 0.0f;
	for (FSpawnEntry Entry : SpawnTable)
	{
		TotalWeight += Entry.Weight;
	}

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AOrbSpawner::SpawnNew,
		SpawnInterval,
		true
	);
}

// Called every frame
void AOrbSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrbSpawner::SpawnNew()
{
	int32 SpawnIndex = ChooseIndex();
	if (SpawnIndex < 0 || !SpawnTable.IsValidIndex(SpawnIndex))
	{
		return;
	}
	TSubclassOf<AActor> SpawnActor = SpawnTable[SpawnIndex].ActorClass;
	if (!SpawnActor)
	{
		return;
	}
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,FString::Printf(TEXT("Spawning Orb")));
	FVector SpawnLocation = ChoosePoint();
	FRotator SpawnRotation = FRotator(0.0f, FMath::FRandRange(0.0f, 360.0f), 0.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	AActor* NewSpawn = GetWorld()->SpawnActor<AActor>(SpawnActor, SpawnLocation, SpawnRotation, SpawnParams);

	if (NewSpawn)
	{
		NewSpawn->OnDestroyed.AddDynamic(this, &AOrbSpawner::HandleChildDestroyed);
		SpawnedActors.Add(NewSpawn);
	}
}

void AOrbSpawner::DestroyAllSpawned()
{
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor && !Actor->IsPendingKillPending())
		{
			Actor->Destroy();
		}
	}
	SpawnedActors.Empty();
}

FVector AOrbSpawner::ChoosePoint()
{
	FVector Origin = SpawnVolume->GetComponentLocation();
	FVector Extent = SpawnVolume->GetScaledBoxExtent();

	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	float BottomZ = Origin.Z - Extent.Z;
	RandomPoint.Z = BottomZ; // Spawn all actors on the same XY plane (bottom face of SpawnVolume)

	return RandomPoint;
}

int32 AOrbSpawner::ChooseIndex()
{
	if (SpawnTable.Num() == 0 || TotalWeight <= 0.0f)
	{
		return -1;
	}

	float RandPoint = FMath::FRandRange(0.0f, TotalWeight);
	float Accum = 0.0f;

	for (int32 i = 0; i < SpawnTable.Num(); i++)
	{
		Accum += SpawnTable[i].Weight;
		if (RandPoint <= Accum)
		{
			return i;
		}
	}

	return SpawnTable.Num() - 1;
}

void AOrbSpawner::HandleChildDestroyed(AActor* DestroyedActor)
{
	SpawnedActors.Remove(DestroyedActor);
}

