// Fill out your copyright notice in the Description page of Project Settings.


#include "BotteryGameState.h"

void ABotteryGameState::AddScore(float Amount)
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

float ABotteryGameState::GetCurrentScore()
{
	return CurrentScore;
}

bool ABotteryGameState::IsGameOver()
{
	return bIsGameOver;
}
