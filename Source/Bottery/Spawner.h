// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnTableDataAsset.h"
#include "Spawner.generated.h"

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

	// This function should be called when SpawnTableDataAsset/OneTimeSpawn/SpawnAmount/SpawnInterval is changed to apply the changes
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void UpdateSpawner();

	UPROPERTY(BlueprintReadWrite, Instanced, Category = "Spawning")
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	USpawnTableDataAsset* SpawnTableDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<AActor*> SpawnedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool OneTimeSpawn = false;

	// The total number of actors that will be spawned when OneTimeSpawn is true
	// The number of actors spawned per interval when OneTimeSpawn is false
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ClampMin = "1"))
	int32 SpawnAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (EditCondition = "!OneTimeSpawn", EditConditionHides, ClampMin = "0.01"))
	float SpawnInterval = 1;

	// Maximum number of spawned actors at any time
	// 0 or -ve value means no limit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (EditCondition = "!OneTimeSpawn", EditConditionHides))
	int32 MaxSpawned = 0;

	FVector ChoosePoint();

	int32 ChooseIndex();

	float TotalWeight;

	FTimerHandle SpawnTimerHandle;

	

	

	
};
