// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbMovementComponent.h"
#include "StatComponent.h"

void UOrbMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UOrbMovementComponent::Init()
{
	UStatComponent* StatComponent = GetOwner()->GetComponentByClass<UStatComponent>();

	if (StatComponent && StatComponent->HasStat(EStatKey::Speed))
	{
		float BaseSpeed = StatComponent->GetStat(EStatKey::Speed)->GetBaseValue();
		InitialSpeed = BaseSpeed;
		MaxSpeed = BaseSpeed;
		Velocity = GetOwner()->GetActorForwardVector() * BaseSpeed;
		UpdateComponentVelocity();

		StatComponent->GetStat(EStatKey::Speed)->OnStatChanged.AddUniqueDynamic(this, &UOrbMovementComponent::UpdateSpeed);

		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Orb speed stat set:%d"),BaseSpeed));
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