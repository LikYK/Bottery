// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;

	HealthDelegateWrapper = CreateDefaultSubobject<UHealthDelegateWrapper>(TEXT("HealthDelegateWrapper"));
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

float UHealthComponent::GetCurrentHealth_Implementation()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth_Implementation()
{
	return MaxHealth;
}

void UHealthComponent::TakeDamage_Implementation(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);

	HealthDelegateWrapper->OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	// Check if owner is dead after taking damage
	if (CurrentHealth <= -MaxHealth || CurrentHealth >= MaxHealth)
	{
		// broadcast death event here
	}

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("Damage: %f, %f"), GetCurrentHealth(), GetMaxHealth())
		);
	}*/
}

UHealthDelegateWrapper* UHealthComponent::GetHealthDelegateWrapper_Implementation()
{
	return HealthDelegateWrapper;
}

