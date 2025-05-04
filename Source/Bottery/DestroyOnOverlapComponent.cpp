// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyOnOverlapComponent.h"
#include "BotteryCharacter.h"

// Sets default values for this component's properties
UDestroyOnOverlapComponent::UDestroyOnOverlapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// Bind handler to destroy on overlap (assumes collision is handled by root component)
	if (AActor* Owner = GetOwner())
	{
		UPrimitiveComponent* CollisionComp = Cast<UPrimitiveComponent>(Owner->GetRootComponent());
		if (CollisionComp)
		{
			CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &UDestroyOnOverlapComponent::DestroyOnOverlap);
		}
	}
}


// Called when the game starts
void UDestroyOnOverlapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDestroyOnOverlapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDestroyOnOverlapComponent::DestroyOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (Pawn->IsPlayerControlled())
		{
			// Only destroy when the other actor is controlled by player
			if (AActor* Owner = GetOwner())
			{
				// Health comp test
				if (ABotteryCharacter* Character = Cast<ABotteryCharacter>(Pawn))
				{
					Character->TakeDamage(10);
				}

				Owner->Destroy();
			}
		}
	}
}

