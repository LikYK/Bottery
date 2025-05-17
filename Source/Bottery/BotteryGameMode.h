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

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void HandleHealthChange(float CurrentHealth, float BaseHealth, float ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void GameOver();
};



