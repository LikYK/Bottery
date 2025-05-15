// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BotteryGameMode.generated.h"

UCLASS(minimalapi)
class ABotteryGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ABotteryGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game Over")
	void CheckForGameOver(float CurrentHealth, float BaseHealth);

	UFUNCTION(BlueprintCallable, Category = Basic)
	void AddScore(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Game Over")
	void GameOver();
};



