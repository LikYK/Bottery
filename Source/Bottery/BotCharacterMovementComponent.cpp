// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacterMovementComponent.h"
#include "StatComponent.h"

void UBotCharacterMovementComponent::BeginPlay()
{ 
	Super::BeginPlay();

	UStatComponent* StatComponent = GetOwner()->GetComponentByClass<UStatComponent>();
	if (StatComponent)
	{
		UStat* Stat = StatComponent->GetStat(EStatKey::Speed);
		if (Stat)
		{
			Stat->StatDelegateWrapper->OnStatChanged.AddUniqueDynamic(this, &UBotCharacterMovementComponent::UpdateSpeed);
			if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Stat Set")));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bot movement component init failed, no speed stat found in stat component."));
		}
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
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("New speed")));
}
