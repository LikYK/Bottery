// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
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
	
	UpdateSpawner();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnNew()
{
	if (!OneTimeSpawn && MaxSpawned > 0 && SpawnedActors.Num() >= MaxSpawned)
	{
		return;
	}

	int32 SpawnIndex = ChooseIndex();
	if (SpawnIndex < 0 || !SpawnTableDataAsset || !SpawnTableDataAsset->SpawnTable.IsValidIndex(SpawnIndex))
	{
		return;
	}
	TSubclassOf<AActor> SpawnActor = SpawnTableDataAsset->SpawnTable[SpawnIndex].ActorClass;
	if (!SpawnActor)
	{
		return;
	}
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,FString::Printf(TEXT("Spawning Orb")));
	FVector SpawnLocation = ChoosePoint();
	FRotator SpawnRotation = FRotator(0.0f, FMath::FRandRange(0.0f, 360.0f), 0.0f);

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
	if (!SpawnTableDataAsset || SpawnTableDataAsset->SpawnTable.Num() == 0 || TotalWeight <= 0.0f)
	{
		return -1;
	}

	float RandPoint = FMath::FRandRange(0.0f, TotalWeight);
	float Accum = 0.0f;

	for (int32 i = 0; i < SpawnTableDataAsset->SpawnTable.Num(); i++)
	{
		Accum += SpawnTableDataAsset->SpawnTable[i].Weight;
		if (RandPoint <= Accum)
		{
			return i;
		}
	}

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
