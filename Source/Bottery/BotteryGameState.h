// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BotteryGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverSignature, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedSignature, int32, NewScore);

UCLASS()
class BOTTERY_API ABotteryGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Basic)
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = Basic)
	void GameOver();

	UFUNCTION(BlueprintCallable, Category = Basic)
	int32 GetCurrentScore();

	UFUNCTION(BlueprintCallable, Category = Basic)
	bool IsGameOver();

	UPROPERTY(BlueprintAssignable, Category = Basic)
	FOnGameOverSignature OnGameOver;

	UPROPERTY(BlueprintAssignable, Category = Basic)
	FOnScoreUpdatedSignature OnScoreUpdated;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
	int32 CurrentScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
	bool bIsGameOver = false;
};
