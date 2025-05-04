// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

int32 UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UHealthComponent::GetHealthBarFill()
{
	// The whole health bar should be 2 * MaxHealth long, from -MaxHealth to MaxHealth
	// Shift everything to the right by MaxHealth so we get minimum 0 on the bar
	// * 1.0f to make result float
	return (CurrentHealth * 1.0f + MaxHealth)/(MaxHealth + MaxHealth);
}

void UHealthComponent::TakeDamage(int32 Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Damage, 0, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, GetHealthBarFill());

	// Check if owner is dead after taking damage
	if (CurrentHealth <= -MaxHealth || CurrentHealth >= MaxHealth)
	{
		// broadcast death event here
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("Damage: %d, %d, %f"), GetCurrentHealth(), GetMaxHealth(), GetHealthBarFill())
		);
	}
}

