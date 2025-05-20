// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "Orb.h"
#include "OrbSpawner.generated.h"

USTRUCT(BlueprintType)
struct FOrbSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpawnTableDataAsset* SpawnTableDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 SpawnAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.01"))
	float SpawnInterval = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxSpawned = 0;
};

UCLASS()
class BOTTERY_API AOrbSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawnInfo(FOrbSpawnInfo SpawnInfo);

protected:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void HandleScoreChanged(float NewScore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TMap<float, FOrbSpawnInfo> SpawnInfos;

	UPROPERTY(BlueprintReadOnly, Category = "Spawning")
	FOrbSpawnInfo CurrentSpawnInfo;
};
