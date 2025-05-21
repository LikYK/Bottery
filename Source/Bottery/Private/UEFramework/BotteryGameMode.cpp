// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEFramework/BotteryGameMode.h"
#include "UEFramework/BotteryPlayerController.h"
#include "Character/BotteryCharacter.h"
#include "PlayerProgression/PlayerProgressSubsystem.h"
#include "UEFramework/BotteryGameState.h"
#include "Kismet/GameplayStatics.h"
#include "ActorData/ResourceComponent.h"
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
	UPlayerProgressSubsystem* Subsys = GetGameInstance()->GetSubsystem<UPlayerProgressSubsystem>();
	ABotteryGameState* GS = GetGameState<ABotteryGameState>();

	if (Subsys)
	{
		Subsys->SaveProgress(GS->GetCurrentScore());
	}

	if (GS)
	{
		GS->GameOver();
	}
}
