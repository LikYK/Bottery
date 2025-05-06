// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEffectComponent.h"

// Sets default values for this component's properties
UTriggerEffectComponent::UTriggerEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnActorBeginOverlap.AddDynamic(this, &UTriggerEffectComponent::HandleOwnerOverlapBegin);
	}
}


// Called every frame
void UTriggerEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerEffectComponent::HandleOwnerOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	ApplyEffect(OtherActor, Magnitude);
}

