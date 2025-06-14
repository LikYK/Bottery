// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorData/ResourceComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UResourceComponent::HasResource(EResourceKey Key)
{
	return Resources.Contains(Key);
}

UResource* UResourceComponent::GetResource(EResourceKey Key)
{
	if (UResource* Resource = Resources.FindRef(Key))
	{
		return Resource;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetResource failed: Resource not found."));
	return nullptr;
}

