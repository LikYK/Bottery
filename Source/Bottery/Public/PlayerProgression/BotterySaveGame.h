// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BotterySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UBotterySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	float HighScore = 0;

	UPROPERTY()
	float MaxHealth = 100;
};
