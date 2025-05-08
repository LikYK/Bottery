// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UStat* UStatComponent::GetStat(EStatKey StatKey)
{
	UStat* Stat = nullptr;

	// Use Find instead of FindRef because FindRef returns a default obj if not found
	UStat** StatPtr = Stats.Find(StatKey);
	if (StatPtr)
	{
		Stat = *StatPtr;
	}

	if (!Stat)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get stat failed, stat not found."));
	}

	return Stat;
}

