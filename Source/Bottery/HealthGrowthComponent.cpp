// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthGrowthComponent.h"

// Sets default values for this component's properties
UHealthGrowthComponent::UHealthGrowthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

int32 UHealthGrowthComponent::GetGrowthRate()
{
	return GrowthRate;
}

void UHealthGrowthComponent::SetGrowthRate(int32 NewRate)
{
	GrowthRate = NewRate;
}

void UHealthGrowthComponent::ChangeGrowthRate(int32 RateChange)
{
	GrowthRate += RateChange;
}


// Called when the game starts
void UHealthGrowthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent = GetOwner()->GetComponentByClass<UHealthComponent>();
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UHealthGrowthComponent requires UHealthComponent to function properly."));
	}
	else 
	{
		GetWorld()->GetTimerManager().SetTimer(
			ApplyTimerHandle,
			this,
			&UHealthGrowthComponent::ApplyGrowthRate,
			1.0f,  // Interval in seconds
			true   // Loop
		);
	}
}

void UHealthGrowthComponent::ApplyGrowthRate()
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(GrowthRate);
	}
}


// Called every frame
void UHealthGrowthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

