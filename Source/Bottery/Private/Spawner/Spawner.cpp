// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/Spawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Setup and start the spawner with the default values
	UpdateSpawner();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnNew()
{
	// If this is not a one-time spawn, make sure currently spawned actors is less than MaxSpawned
	if (!OneTimeSpawn && MaxSpawned > 0 && SpawnedActors.Num() >= MaxSpawned)
	{
		return;
	}

	// Choose a random index and make sure it is valid before continuing
	int32 SpawnIndex = ChooseIndex();
	if (SpawnIndex < 0 || !SpawnTableDataAsset || !SpawnTableDataAsset->SpawnTable.IsValidIndex(SpawnIndex))
	{
		return;
	}
	// Get the actor to spawn from the spawn table with the index
	TSubclassOf<AActor> SpawnActor = SpawnTableDataAsset->SpawnTable[SpawnIndex].ActorClass;
	if (!SpawnActor)
	{
		return;
	}
	
	FVector SpawnLocation = ChoosePoint(); //Random point in SpawnVolume's base/bottom face
	FRotator SpawnRotation = FRotator(0.0f, FMath::FRandRange(0.0f, 360.0f), 0.0f); // Random yaw rotation

	AActor* NewSpawn = GetWorld()->SpawnActor<AActor>(SpawnActor, SpawnLocation, SpawnRotation);

	if (NewSpawn)
	{
		NewSpawn->OnDestroyed.AddDynamic(this, &ASpawner::HandleChildDestroyed);
		SpawnedActors.Add(NewSpawn);
	}
}

void ASpawner::SpawnMultiple(int32 Amount)
{
	int32 StartingCount = SpawnedActors.Num();
	int32 TargetCount = StartingCount + Amount;
	int32 Tries = 0;

	// Use a while loop instead of for loop so actors that don't spawn if colliding can get multiple tries instead of getting skipped
	// Limit amount of tries to prevent infinite loop if spawning is not possible
	while (SpawnedActors.Num() < TargetCount && Tries < Amount * 10)
	{
		Tries++;

		SpawnNew();
	}
}

void ASpawner::DestroyAllSpawned()
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

FVector ASpawner::ChoosePoint()
{
	FVector Origin = SpawnVolume->GetComponentLocation();
	FVector Extent = SpawnVolume->GetScaledBoxExtent();

	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	float BottomZ = Origin.Z - Extent.Z;
	RandomPoint.Z = BottomZ; // Spawn all actors on the same XY plane (bottom face of SpawnVolume)

	return RandomPoint;
}

int32 ASpawner::ChooseIndex()
{
	// Make sure there is a spawn table with entries and a valid weight before continuing
	if (!SpawnTableDataAsset || SpawnTableDataAsset->SpawnTable.Num() == 0 || TotalWeight <= 0.0f)
	{
		return -1;
	}

	float RandPoint = FMath::FRandRange(0.0f, TotalWeight);
	float Accum = 0.0f;

	for (int32 i = 0; i < SpawnTableDataAsset->SpawnTable.Num(); i++)
	{
		// For each entry in spawn table, add its weight to Accum
		Accum += SpawnTableDataAsset->SpawnTable[i].Weight;
		// If accumulated weight after adding this entry is higher than the random value, 
		// that means the random value falls in this entry's weight in the spawn table
		if (RandPoint <= Accum)
		{
			return i;
		}
	}

	// Fallback value, this should not run
	UE_LOG(LogTemp, Warning, TEXT("ASpawner::ChooseIndex: Using fallback value, something is wrong!"));
	return SpawnTableDataAsset->SpawnTable.Num() - 1;
}

void ASpawner::HandleChildDestroyed(AActor* DestroyedActor)
{
	SpawnedActors.Remove(DestroyedActor);
}

void ASpawner::UpdateSpawner()
{
	TotalWeight = 0.0f;
	if (SpawnTableDataAsset)
	{
		for (FSpawnEntry Entry : SpawnTableDataAsset->SpawnTable)
		{
			TotalWeight += Entry.Weight;
		}
	}

	if (OneTimeSpawn)
	{
		SpawnMultiple(SpawnAmount);
	}
	else
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(this, &ASpawner::SpawnMultiple, SpawnAmount);

		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			Delegate,
			SpawnInterval,
			true
		);
	}
}
