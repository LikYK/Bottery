// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacterMovementComponent.h"
#include "StatComponent.h"

void UBotCharacterMovementComponent::BeginPlay()
{ 
	Super::BeginPlay();

	auto StatComponents = GetOwner()->GetComponentsByInterface(UStatInterface::StaticClass());
	if (!StatComponents.IsEmpty())
	{
		UActorComponent* StatComponent = StatComponents[0];

		MaxWalkSpeed = IStatInterface::Execute_GetStatBase(StatComponent, EStatKey::Speed);

		if (UStatDelegateWrapper* DelegateWrapper = IStatInterface::Execute_GetStatDelegateWrapper(StatComponent, EStatKey::Speed))
		{
			DelegateWrapper->OnStatChanged.AddUniqueDynamic(this, &UBotCharacterMovementComponent::UpdateSpeed);
		}

		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Speed stat set:%d"), MaxWalkSpeed));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot movement component init failed, no stat component found in owner."));
	}
}

void UBotCharacterMovementComponent::UpdateSpeed(float NewSpeed, float BaseSpeed)
{
	// Base speed is not used here, it is used in HUD display. The param allows this func to be bound to the delegate.

	MaxWalkSpeed = NewSpeed;
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("New speed")));
}
