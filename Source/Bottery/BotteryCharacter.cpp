// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryCharacter.h"
#include "BotCharacterMovementComponent.h"
#include "PlayerProgressSubsystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
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

	// Add a default polarity component
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bOverrideAttenuation = true;
}

void ABotteryCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (UPlayerProgressSubsystem* Subsys = GetGameInstance()->GetSubsystem<UPlayerProgressSubsystem>())
	{
		// Set MaxHealth as value loaded in PlayerProgressSubsystem
		UResource* HealthResource = ResourceComponent->GetResource(EResourceKey::Health);
		HealthResource->SetMaxValue(Subsys->GetMaxHealth());
		// CurrentHealth also needs to be reset because Resource's InitValue/CurrentValue=MaxValue is called before BeginPlay
		// Use InitValue instead of SetValue to prevent health's OnResourceChanged from firing
		HealthResource->InitValue();
	}

	// Link health decay rate to magnitude(multiplier) stat
	UStat* MagnitudeStat = StatComponent->GetStat(EStatKey::Magnitude);
	UStat* HealthRegenStat = ResourceComponent->GetResource(EResourceKey::Health)->GetRegenRateStat();
	HealthRegenStat->SetValue(HealthRegenStat->GetBaseValue() * MagnitudeStat->GetBaseValue());
	MagnitudeStat->OnStatChanged.AddUniqueDynamic(this, &ABotteryCharacter::HandleMagnitudeChange);

	// Link stamina regen rate to speed stat
	UStat* SpeedStat = StatComponent->GetStat(EStatKey::Speed);
	SpeedStat->OnStatChanged.AddUniqueDynamic(this, &ABotteryCharacter::HandleSpeedChange);
}

void ABotteryCharacter::Dash()
{
	if (!bCanDash) return;

	// Check stamina
	if (!UseStamina(DashStamina))
	{
		return;
	}

	// Get direction
	FVector Dir = GetActorForwardVector();

	// Launch character
	LaunchCharacter(Dir * DashVelocity, true, false);

	// Play dash animation
	if (DashMontage)
	{
		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
		if (AnimInst && !AnimInst->Montage_IsPlaying(DashMontage))
		{
			AnimInst->Montage_Play(DashMontage);
		}
	}

	// Play audio
	AudioComponent->SetSound(DashSound);
	AudioComponent->Play();

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
	if (!FlagComponent || !FlagComponent->HasFlag(EFlagKey::Polarity))
	{
		UE_LOG(LogTemp, Warning, TEXT("Changing polarity failed: No polarity handling component found."));
	}

	// Check stamina
	if (!UseStamina(ChangePolarityStamina))
	{
		return;
	}

	FlagComponent->GetFlag(EFlagKey::Polarity)->SwitchValue();

	// Play audio
	AudioComponent->SetSound(ChangePolaritySound);
	AudioComponent->Play();
}

// Attempts to use stamina, return true if successfully used and false otherwise.
bool ABotteryCharacter::UseStamina(float Amount)
{
	if (ResourceComponent && ResourceComponent->HasResource(EResourceKey::Stamina))
	{
		UResource* Stamina = ResourceComponent->GetResource(EResourceKey::Stamina);

		if (Stamina->GetValue() >= Amount)
		{
			Stamina->ModifyValue(-Amount);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ABotteryCharacter::UseStamina failed: Character has no stamina resource."));
		return false;
	}
}

// Changes health decay rate with magnitude stat value passed in
void ABotteryCharacter::HandleMagnitudeChange(float CurrentValue, float BaseValue)
{
	UStat* HealthRegenStat = ResourceComponent->GetResource(EResourceKey::Health)->GetRegenRateStat();

	HealthRegenStat->SetValue(HealthRegenStat->GetBaseValue() * CurrentValue);
}

// Changes stamina regen rate with spped stat value passed in
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
