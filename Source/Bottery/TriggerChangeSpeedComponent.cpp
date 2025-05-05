// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeSpeedComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTriggerChangeSpeedComponent::ApplyEffect(AActor* Target, float EffectMagnitude, int8 Polarity)
{
	if (ACharacter* Character = Cast<ACharacter>(Target))
	{
		Character->GetCharacterMovement()->MaxWalkSpeed += Polarity * EffectMagnitude;
	}
}