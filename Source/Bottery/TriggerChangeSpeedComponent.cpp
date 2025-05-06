// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeSpeedComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PolarityComponent.h"

void UTriggerChangeSpeedComponent::ApplyEffect(AActor* Target, float EffectMagnitude)
{
	if (ACharacter* Character = Cast<ACharacter>(Target))
	{
		if (UPolarityComponent* PolarityComponent = GetOwner()->GetComponentByClass<UPolarityComponent>())
		{
			EPolarity Polarity = PolarityComponent->GetPolarity();

			if (Polarity == EPolarity::Positive)
			{
				Character->GetCharacterMovement()->MaxWalkSpeed += EffectMagnitude;
			}
			else 
			{
				Character->GetCharacterMovement()->MaxWalkSpeed -= EffectMagnitude;
			}
		}
	}
}