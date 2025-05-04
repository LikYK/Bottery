// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ABotteryCharacter::ABotteryCharacter()
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

	// Add a default health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABotteryCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Link the OnHealthChange broadcast
	// this is done so that the delegate can be bound to from outside without directly accessing health component
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUniqueDynamic(this, &ABotteryCharacter::BroadcastHealthChangedInternal);
	}
}

void ABotteryCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ABotteryCharacter::TakeDamage(int32 Damage)
{
	HealthComponent->TakeDamage(Damage);
}

int32 ABotteryCharacter::GetCurrentHealth()
{
	return HealthComponent->GetCurrentHealth();
}

int32 ABotteryCharacter::GetMaxHealth()
{
	return HealthComponent->GetMaxHealth();
}

float ABotteryCharacter::GetHealthBarFill()
{
	return HealthComponent->GetHealthBarFill();
}

void ABotteryCharacter::BroadcastHealthChangedInternal(int32 CurrentHealth, int32 MaxHealth, float Fill)
{
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, Fill);
}