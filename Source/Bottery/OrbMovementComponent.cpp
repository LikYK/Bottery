// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbMovementComponent.h"
#include "StatComponent.h"

void UOrbMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> StatComponents = GetOwner()->GetComponentsByInterface(UStatInterface::StaticClass());
	UActorComponent* StatComponent = nullptr;

	if (StatComponents.Num() > 0)
	{
		StatComponent = StatComponents[0];
	}

	if (StatComponent)
	{
		float BaseSpeed = IStatInterface::Execute_GetStatBase(StatComponent, EStatKey::Speed);
		InitialSpeed = BaseSpeed;
		MaxSpeed = BaseSpeed;
		Velocity = Velocity.GetSafeNormal() * BaseSpeed;
		UpdateComponentVelocity();

		if (UStatDelegateWrapper* DelegateWrapper = IStatInterface::Execute_GetStatDelegateWrapper(StatComponent, EStatKey::Speed))
		{
			DelegateWrapper->OnStatChanged.AddUniqueDynamic(this, &UOrbMovementComponent::UpdateSpeed);
		}

		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Orb speed stat set:%d"),BaseSpeed));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot movement component init failed, no stat component found in owner."));
	}
}

void UOrbMovementComponent::UpdateSpeed(float NewSpeed, float BaseSpeed)
{
	// Base speed is not used here, it is used in HUD display. The param allows this func to be bound to the delegate.

	InitialSpeed = BaseSpeed;
	MaxSpeed = NewSpeed;
	Velocity = Velocity.GetSafeNormal() * NewSpeed;
	UpdateComponentVelocity();
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("New speed")));
}