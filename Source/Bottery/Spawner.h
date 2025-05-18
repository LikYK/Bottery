// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Spawner.generated.h"

USTRUCT(BlueprintType)
struct FSpawnEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ClampMin = "0.0"))
	float Weight = 1.0f;
};

UCLASS()
class BOTTERY_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnNew();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnMultiple(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void DestroyAllSpawned();

protected:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void HandleChildDestroyed(AActor* DestroyedActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Spawning")
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FSpawnEntry> SpawnTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<AActor*> SpawnedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool OneTimeSpawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ClampMin = "1"))
	int32 SpawnAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (EditCondition = "!OneTimeSpawn", EditConditionHides, ClampMin = "0.01"))
	float SpawnInterval = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (EditCondition = "!OneTimeSpawn", EditConditionHides))
	int32 MaxSpawned = 0;

	FVector ChoosePoint();

	int32 ChooseIndex();

	float TotalWeight;

	FTimerHandle SpawnTimerHandle;

	

	

	
};
