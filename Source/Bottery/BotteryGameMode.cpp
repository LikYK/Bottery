// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryGameMode.h"
#include "BotteryPlayerController.h"
#include "BotteryCharacter.h"
#include "PlayerProgressSubsystem.h"
#include "BotteryGameState.h"
#include "Kismet/GameplayStatics.h"
#include "ResourceComponent.h"
#include "UObject/ConstructorHelpers.h"

void ABotteryGameMode::BeginPlay()
{
	// Bind to health delegates to update score and check for game over
	if (ABotteryCharacter* PlayerCharacter = Cast<ABotteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		UResourceComponent* ResourceComponent = PlayerCharacter->GetComponentByClass<UResourceComponent>();
		if (ResourceComponent && ResourceComponent->HasResource(EResourceKey::Health))
		{
			UResource* Health = ResourceComponent->GetResource(EResourceKey::Health);

			Health->OnResourceChanged.AddUniqueDynamic(this, &ABotteryGameMode::HandleHealthChange);
		}
	}

	// Bind PlayerProgressSubsystem's save to GameState's GameOver
	if (UPlayerProgressSubsystem* Subsys = GetGameInstance()->GetSubsystem<UPlayerProgressSubsystem>())
	{
		if (ABotteryGameState* GS = GetGameState<ABotteryGameState>())
		{
			GS->OnGameOver.AddUniqueDynamic(Subsys, &UPlayerProgressSubsystem::SaveProgress);
		}
	}
}

ABotteryGameMode::ABotteryGameMode()
{
}

void ABotteryGameMode::HandleHealthChange(float CurrentHealth, float BaseHealth, float ChangeAmount)
{
	ABotteryGameState* GS = GetGameState<ABotteryGameState>();

	// Add score if this change is a heal
	if (ChangeAmount > 0.0f)
	{
		GS->AddScore(ChangeAmount);
	}

	// Game over if health reaches 0
	if (!GS->IsGameOver() && CurrentHealth <= 0)
	{
		GameOver();
	}
}

void ABotteryGameMode::GameOver()
{
	if (ABotteryGameState* GS = GetGameState<ABotteryGameState>())
	{
		GS->GameOver();
	}
}
