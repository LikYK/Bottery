// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentStamina = MaxStamina;

	StaminaDelegateWrapper = CreateDefaultSubobject<UStaminaDelegateWrapper>(TEXT("StaminaDelegateWrapper"));
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UseStamina(-RegenRate * DeltaTime);
}

float UStaminaComponent::GetCurrentStamina()
{
	return CurrentStamina;
}

float UStaminaComponent::GetMaxStamina()
{
	return MaxStamina;
}

void UStaminaComponent::UseStamina(float UseAmount)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - UseAmount, 0, MaxStamina);

	StaminaDelegateWrapper->OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}

float UStaminaComponent::GetRegenRate()
{
	return RegenRate;
}

void UStaminaComponent::SetRegenRate(float NewRate)
{
	RegenRate = NewRate;
}

void UStaminaComponent::ModifyRegenRate(float RateChange)
{
	RegenRate += RateChange;
}

UStaminaDelegateWrapper* UStaminaComponent::GetStaminaDelegateWrapper()
{
	return StaminaDelegateWrapper;
}

