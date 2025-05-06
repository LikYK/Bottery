// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeHealthComponent.h"
#include "BotteryCharacter.h"
#include "PolarityComponent.h"

void UTriggerChangeHealthComponent::ApplyEffect(AActor* Target, float EffectMagnitude)
{
	if (ABotteryCharacter* BotteryCharacter = Cast<ABotteryCharacter>(Target))
	{
		EPolarity CharacterPolarity = BotteryCharacter->GetComponentByClass<UPolarityComponent>()->GetPolarity();
		if (UPolarityComponent* PolarityComponent = GetOwner()->GetComponentByClass<UPolarityComponent>())
		{
			EPolarity Polarity = PolarityComponent->GetPolarity();

			// Heals character if same polarity, deals damage otherwise
			if (Polarity == CharacterPolarity)
			{
				BotteryCharacter->TakeDamage(-EffectMagnitude);
			}
			else 
			{
				BotteryCharacter->TakeDamage(EffectMagnitude);
			}
		}
	}
}
