// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorData/FlagComponent.h"

// Sets default values for this component's properties
UFlagComponent::UFlagComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFlagComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFlagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UFlagComponent::HasFlag(EFlagKey Key)
{
	return Flags.Contains(Key);
}

UFlag* UFlagComponent::GetFlag(EFlagKey Key)
{
	if (UFlag* Flag = Flags.FindRef(Key))
	{
		return Flag;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetFlag failed: Flag not found."));
	return nullptr;
}

