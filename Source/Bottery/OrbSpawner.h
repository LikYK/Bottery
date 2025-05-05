// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "OrbSpawner.generated.h"

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
class BOTTERY_API AOrbSpawner : public AActor
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
	void SpawnNew();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void DestroyAllSpawned();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<FSpawnEntry> SpawnTable;

	float TotalWeight;

	FVector ChoosePoint();

	int32 ChooseIndex();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<AActor*> SpawnedActors;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void HandleChildDestroyed(AActor* DestroyedActor);

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 1;

};
