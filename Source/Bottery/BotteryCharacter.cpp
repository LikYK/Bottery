// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryCharacter.h"
#include "BotCharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ABotteryCharacter::ABotteryCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UBotCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Add a default stat component
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stats"));

	// Add a default health component
	ResourceComponent = CreateDefaultSubobject<UResourceComponent>(TEXT("Resources"));
	
	// Add a default polarity component
	FlagComponent = CreateDefaultSubobject<UFlagComponent>(TEXT("Flags"));
}

void ABotteryCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	UStat* MagnitudeStat = StatComponent->GetStat(EStatKey::Magnitude);
	UStat* SpeedStat = StatComponent->GetStat(EStatKey::Speed);

	UStat* HealthRegenStat = ResourceComponent->GetResource(EResourceKey::Health)->GetRegenRateStat();
	HealthRegenStat->SetValue(HealthRegenStat->GetBaseValue() * MagnitudeStat->GetBaseValue());

	MagnitudeStat->OnStatChanged.AddUniqueDynamic(this, &ABotteryCharacter::HandleMagnitudeChange);
	SpeedStat->OnStatChanged.AddUniqueDynamic(this, &ABotteryCharacter::HandleSpeedChange);
}

void ABotteryCharacter::Dash()
{
	if (!bCanDash) return;

	// Check stamina
	if (ResourceComponent && ResourceComponent->HasResource(EResourceKey::Stamina))
	{
		UResource* Stamina = ResourceComponent->GetResource(EResourceKey::Stamina);

		if (Stamina->GetValue() >= 10)
		{
			Stamina->ModifyValue(-10);
		}
		else
		{
			if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("No stamina, no dash")));
			return;
		}
	}
	else
	{
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("No stamina resource")));
	}

	// Get direction
	FVector Dir = GetActorForwardVector();

	// Launch character
	LaunchCharacter(Dir * DashVelocity, true, false);

	// Cooldown
	bCanDash = false;

	TWeakObjectPtr<ABotteryCharacter> SafeThis(this);
	GetWorldTimerManager().SetTimer(
		DashCooldownTimer, 
		FTimerDelegate::CreateLambda([this, SafeThis]()
			{
				if (SafeThis.IsValid())
				{
					bCanDash = true;
				}
			}),
		DashCooldown, 
		false);
}

void ABotteryCharacter::ChangePolarity()
{
	if (FlagComponent && FlagComponent->HasFlag(EFlagKey::Polarity))
	{
		FlagComponent->GetFlag(EFlagKey::Polarity)->SwitchValue();

		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Polarity changed, polarity:%d"), FlagComponent->GetFlag(EFlagKey::Polarity)->GetValue()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Changing polarity failed: No polarity handling component found."));
	}
}

void ABotteryCharacter::HandleMagnitudeChange(float CurrentValue, float BaseValue)
{
	UStat* HealthRegenStat = ResourceComponent->GetResource(EResourceKey::Health)->GetRegenRateStat();

	HealthRegenStat->SetValue(HealthRegenStat->GetBaseValue() * CurrentValue);
}

void ABotteryCharacter::HandleSpeedChange(float CurrentValue, float BaseValue)
{
	UStat* StaminaRegenStat = ResourceComponent->GetResource(EResourceKey::Stamina)->GetRegenRateStat();
	float Multiplier = CurrentValue / BaseValue;

	StaminaRegenStat->SetValue(StaminaRegenStat->GetBaseValue() * (1.0f / Multiplier));
}

void ABotteryCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
