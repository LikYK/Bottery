// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorData/StatComponent.h"

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

bool UStatComponent::HasStat(EStatKey Key)
{
	return Stats.Contains(Key);
}

UStat* UStatComponent::GetStat(EStatKey Key)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetStat failed: Stat not found."));
	return nullptr;
}