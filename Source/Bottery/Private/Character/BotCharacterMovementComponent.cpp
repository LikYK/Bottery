// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BotCharacterMovementComponent.h"
#include "ActorData/StatComponent.h"

void UBotCharacterMovementComponent::BeginPlay()
{ 
	Super::BeginPlay();

	UStatComponent* StatComponent = GetOwner()->GetComponentByClass<UStatComponent>();
	if (StatComponent && StatComponent->HasStat(EStatKey::Speed))
	{
		UStat* SpeedStat = StatComponent->GetStat(EStatKey::Speed);

		MaxWalkSpeed = SpeedStat->GetValue();

		SpeedStat->OnStatChanged.AddUniqueDynamic(this, &UBotCharacterMovementComponent::UpdateSpeed);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot movement component init failed, no speed stat found in owner."));
	}
}

void UBotCharacterMovementComponent::UpdateSpeed(float NewSpeed, float BaseSpeed)
{
	// Base speed is not used here, it is used in HUD display. The param allows this func to be bound to the delegate.

	MaxWalkSpeed = NewSpeed;
}
