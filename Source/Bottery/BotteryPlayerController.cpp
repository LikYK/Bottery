// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryPlayerController.h"
#include "StaminaComponent.h"
#include "BotCharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BotteryCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "BotteryGameState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABotteryPlayerController::ABotteryPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ABotteryPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Create and add HUD widget
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}

	// Show game over UI on game over
	if (ABotteryGameState* GameState = Cast<ABotteryGameState>(GetWorld()->GetGameState()))
	{
		GameState->OnGameOver.AddUniqueDynamic(this, &ABotteryPlayerController::ShowGameOverUI);
	}
}

void ABotteryPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ABotteryPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ABotteryPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ABotteryPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ABotteryPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ABotteryPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ABotteryPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ABotteryPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ABotteryPlayerController::OnTouchReleased);

		// Change polarity
		EnhancedInputComponent->BindAction(ChangePolarityAction, ETriggerEvent::Triggered, this, &ABotteryPlayerController::OnChangePolarity);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ABotteryPlayerController::OnDash);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABotteryPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ABotteryPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ABotteryPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ABotteryPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ABotteryPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ABotteryPlayerController::OnChangePolarity()
{
	APawn* ControlledPawn = GetPawn();

	UFlagComponent* FlagComponent = ControlledPawn->GetComponentByClass<UFlagComponent>();
	if (FlagComponent && FlagComponent->HasFlag(EFlagKey::Polarity))
	{
		FlagComponent->GetFlag(EFlagKey::Polarity)->SwitchValue();

		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Polarity changed, polarity:%d"), FlagComponent->GetFlag(EFlagKey::Polarity)->GetValue()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Changing polarity failed: No polarity handling component found in player-controlled pawn."));
	}
}

void ABotteryPlayerController::OnDash()
{
	if (!bCanDash) return;
	
	// Check stamina
	UStaminaComponent* StaminaComponent = GetPawn()->GetComponentByClass<UStaminaComponent>();
	if (StaminaComponent)
	{
		if (StaminaComponent->GetCurrentStamina() >= 10)
		{
			StaminaComponent->UseStamina(10);
		}
		else 
		{
			if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("No stamina, no dash")));
			return;
		}
	}
	else
	{
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("No stamina comp")));
	}

	// Get direction
	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());
	FVector Dir = GetPawn()->GetActorForwardVector();

	// Launch character
	ControlledCharacter->LaunchCharacter(Dir * DashDistance, true, false);

	// Cooldown
	bCanDash = false;
	GetWorldTimerManager().SetTimer(DashCooldownTimer, this, &ABotteryPlayerController::ResetCanDash, DashCooldown, false);
}

void ABotteryPlayerController::ResetCanDash()
{
	bCanDash = true;
}

void ABotteryPlayerController::ShowGameOverUI(int32 Score)
{
	if (GameOverWidgetClass && !GameOverWidgetInstance)
	{
		GameOverWidgetInstance = CreateWidget<UUserWidget>(this, GameOverWidgetClass);
	}

	if (GameOverWidgetInstance)
	{
		if (!GameOverWidgetInstance->IsInViewport())
		{
			GameOverWidgetInstance->AddToViewport();
		}

		GameOverWidgetInstance->SetVisibility(ESlateVisibility::Visible);

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		//FInputModeUIOnly InputMode;
		//InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
		//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		//SetInputMode(InputMode);
		//bShowMouseCursor = true;
	}
}

void ABotteryPlayerController::ShowPauseUI()
{
	if (PauseWidgetClass && !PauseWidgetInstance)
	{
		PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);
	}

	if (PauseWidgetInstance)
	{
		if (!PauseWidgetInstance->IsInViewport())
		{
			PauseWidgetInstance->AddToViewport();
		}

		PauseWidgetInstance->SetVisibility(ESlateVisibility::Visible);

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void ABotteryPlayerController::ShowTutorialUI()
{
	if (TutorialWidgetClass && !TutorialWidgetInstance)
	{
		TutorialWidgetInstance = CreateWidget<UUserWidget>(this, TutorialWidgetClass);
	}

	if (TutorialWidgetInstance)
	{
		if (!TutorialWidgetInstance->IsInViewport()) 
		{
			TutorialWidgetInstance->AddToViewport();
		}

		TutorialWidgetInstance->SetVisibility(ESlateVisibility::Visible);

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
