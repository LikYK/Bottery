// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthDecayComponent.h"

// Sets default values for this component's properties
UHealthDecayComponent::UHealthDecayComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthDecayComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> HealthComponents = GetOwner()->GetComponentsByInterface(UHealthInterface::StaticClass());
	if (HealthComponents.Num() > 0)
	{
		HealthComponent = HealthComponents[0];
	}
	
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UHealthDecayComponent requires a component that implements IHealthInterface to function properly."));
	}
	
}


// Called every frame
void UHealthDecayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HealthComponent)
	{
		IHealthInterface::Execute_TakeDamage(HealthComponent, DecayRate * DeltaTime);
	}
}

float UHealthDecayComponent::GetDecayRate()
{
	return DecayRate;
}

void UHealthDecayComponent::SetDecayRate(float NewRate)
{
	DecayRate = NewRate;
}

void UHealthDecayComponent::ChangeDecayRate(float RateChange)
{
	DecayRate += RateChange;
}

