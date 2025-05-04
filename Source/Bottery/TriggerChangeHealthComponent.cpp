// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeHealthComponent.h"
#include "BotteryCharacter.h"

void UTriggerChangeHealthComponent::ApplyEffect(AActor* Target, float EffectMagnitude, int8 Polarity)
{
	if (ABotteryCharacter* BotteryCharacter = Cast<ABotteryCharacter>(Target))
	{
		BotteryCharacter->TakeDamage(Polarity * EffectMagnitude);
	}
}
