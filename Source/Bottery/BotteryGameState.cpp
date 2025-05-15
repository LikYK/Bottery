// Fill out your copyright notice in the Description page of Project Settings.


#include "BotteryGameState.h"

void ABotteryGameState::AddScore(int32 Amount)
{
	if (!bIsGameOver)
	{
		CurrentScore += Amount;
		OnScoreUpdated.Broadcast(CurrentScore);
	}
}

void ABotteryGameState::GameOver()
{
	bIsGameOver = true;
	OnGameOver.Broadcast(CurrentScore);
}

int32 ABotteryGameState::GetCurrentScore()
{
	return CurrentScore;
}

bool ABotteryGameState::IsGameOver()
{
	return bIsGameOver;
}
