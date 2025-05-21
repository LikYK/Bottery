// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BotteryGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOverSignature, float, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedSignature, float, NewScore);

UCLASS()
class BOTTERY_API ABotteryGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Game Over")
	void GameOver();

	UFUNCTION(BlueprintCallable, Category = "Score")
	float GetCurrentScore();

	UFUNCTION(BlueprintCallable, Category = "Game Over")
	bool IsGameOver();

	UPROPERTY(BlueprintAssignable, Category = "Game Over")
	FOnGameOverSignature OnGameOver;

	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreUpdatedSignature OnScoreUpdated;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	float CurrentScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
	bool bIsGameOver = false;
};
