// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryGameMode.h"
#include "BotteryPlayerController.h"
#include "BotteryCharacter.h"
#include "PlayerProgressSubsystem.h"
#include "BotteryGameState.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "UObject/ConstructorHelpers.h"

void ABotteryGameMode::BeginPlay()
{
	// Bind to health delegates to update score and check for game over
	if (ABotteryCharacter* PlayerCharacter = Cast<ABotteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		if (UHealthComponent* HealthComponent = PlayerCharacter->GetComponentByClass<UHealthComponent>())
		{
			HealthComponent->GetHealthDelegateWrapper()->OnHealthChanged.AddUniqueDynamic(this, &ABotteryGameMode::CheckForGameOver);
			HealthComponent->GetHealthDelegateWrapper()->OnHealed.AddUniqueDynamic(this, &ABotteryGameMode::AddScore);
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

void ABotteryGameMode::CheckForGameOver(float CurrentHealth, float BaseHealth)
{
	ABotteryGameState* GS = GetGameState<ABotteryGameState>();

	if (!GS->IsGameOver() && CurrentHealth <= 0)
	{
		GameOver();
	}
}

void ABotteryGameMode::AddScore(float Amount)
{
	ABotteryGameState* GS = GetGameState<ABotteryGameState>();
	if (GS)
	{
		GS->AddScore(Amount);
	}
}

void ABotteryGameMode::GameOver()
{
	if (ABotteryGameState* GS = GetGameState<ABotteryGameState>())
	{
		GS->GameOver();
	}
}
