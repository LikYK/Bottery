// Copyright Epic Games, Inc. All Rights Reserved.

#include "BotteryCharacter.h"
#include "BotCharacterMovementComponent.h"
#include "StatDelegateWrapper.h"
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
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	// Add a default polarity component
	PolarityComponent = CreateDefaultSubobject<UPolarityComponent>(TEXT("Polarity"));
}

void ABotteryCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ABotteryCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Health
//void ABotteryCharacter::TakeDamage_Implementation(float Damage)
//{
//	HealthComponent->TakeDamage(Damage);
//}
//
//float ABotteryCharacter::GetCurrentHealth_Implementation()
//{
//	return HealthComponent->GetCurrentHealth();
//}
//
//float ABotteryCharacter::GetMaxHealth_Implementation()
//{
//	return HealthComponent->GetMaxHealth();
//}
//
//UHealthDelegateWrapper* ABotteryCharacter::GetHealthDelegateWrapper_Implementation()
//{
//	return HealthComponent->HealthDelegateWrapper;
//}
//
//bool ABotteryCharacter::HasStat_Implementation(EStatKey Key)
//{
//	return StatComponent->HasStat(Key);
//}
//
//float ABotteryCharacter::GetStatBase_Implementation(EStatKey Key)
//{
//	return StatComponent->GetStatBase(Key);
//}
//
//float ABotteryCharacter::GetStatMax_Implementation(EStatKey Key)
//{
//	return StatComponent->GetStatMax(Key);
//}
//
//float ABotteryCharacter::GetStatMin_Implementation(EStatKey Key)
//{
//	return StatComponent->GetStatMin(Key);
//}
//
//float ABotteryCharacter::GetStatValue_Implementation(EStatKey Key)
//{
//	return StatComponent->GetStatValue(Key);
//}
//
//void ABotteryCharacter::SetStatValue_Implementation(EStatKey Key, float NewValue)
//{
//	StatComponent->SetStatValue(Key, NewValue);
//}
//
//void ABotteryCharacter::ModifyStat_Implementation(EStatKey Key, float ChangeAmount)
//{
//	StatComponent->ModifyStat(Key, ChangeAmount);
//}
//
//UStatDelegateWrapper* ABotteryCharacter::GetStatDelegateWrapper_Implementation(EStatKey Key)
//{
//	return StatComponent->GetStatDelegateWrapper(Key);
//}

// Speed
//float ABotteryCharacter::GetBaseSpeed_Implementation()
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat)) 
//	{
//		return Stat->GetBaseValue();
//	}
//	else 
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetBaseSpeed failed, speed stat is not valid."));
//		return 0.0f;
//	}
//}
//
//float ABotteryCharacter::GetMaxSpeed_Implementation()
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat))
//	{
//		return Stat->GetMaxValue();
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetMaxSpeed failed, speed stat is not valid."));
//		return 0.0f;
//	}
//}
//
//float ABotteryCharacter::GetMinSpeed_Implementation()
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat))
//	{
//		return Stat->GetMinValue();
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetMinSpeed failed, speed stat is not valid."));
//		return 0.0f;
//	}
//}
//
//float ABotteryCharacter::GetCurrentSpeed_Implementation()
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat))
//	{
//		return Stat->GetValue();
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetCurrentSpeed failed, speed stat is not valid."));
//		return 0.0f;
//	}
//}
//
//void ABotteryCharacter::SetSpeed_Implementation(float NewValue)
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat))
//	{
//		Stat->SetValue(NewValue);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("SetSpeed failed, speed stat is not valid."));
//	}
//}
//
//void ABotteryCharacter::ModifySpeed_Implementation(float ChangeAmount)
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat))
//	{
//		Stat->ModifyValue(ChangeAmount);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ModifySpeed failed, speed stat is not valid."));
//	}
//}
//
//UStatDelegateWrapper* ABotteryCharacter::GetSpeedDelegateWrapper_Implementation()
//{
//	UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
//	if (IsValid(Stat))
//	{
//		return Stat->StatDelegateWrapper;
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetSpeedDelegateWrapper failed, speed stat is not valid."));
//		return nullptr;
//	}
//}

//EPolarity ABotteryCharacter::GetPolarity_Implementation()
//{
//	return PolarityComponent->GetPolarity();
//}
//
//void ABotteryCharacter::SetPolarity_Implementation(EPolarity NewPolarity)
//{
//	PolarityComponent->SetPolarity(NewPolarity);
//}
//
//void ABotteryCharacter::SwitchPolarity_Implementation()
//{
//	PolarityComponent->SwitchPolarity();
//}
//
//FLinearColor ABotteryCharacter::GetPolarityColour_Implementation()
//{
//	return PolarityComponent->GetPolarityColour();
//}
//
//UPolarityDelegateWrapper* ABotteryCharacter::GetPolarityDelegateWrapper_Implementation()
//{
//	return PolarityComponent->PolarityDelegateWrapper;
//}

// Polarity
//EPolarity ABotteryCharacter::GetPolarity()
//{
//	return PolarityComponent->GetPolarity();
//}
//
//void ABotteryCharacter::SetPolarity(EPolarity NewPolarity)
//{
//	PolarityComponent->SetPolarity(NewPolarity);
//}
//
//void ABotteryCharacter::SwitchPolarity()
//{
//	PolarityComponent->SwitchPolarity();
//}
