// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "OrbSpawner.generated.h"

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

protected:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void HandleScoreChanged(float NewScore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TMap<float, int32> ScoreMaxSpawns;
};
