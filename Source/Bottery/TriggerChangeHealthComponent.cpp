// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeHealthComponent.h"
#include "BotteryCharacter.h"
#include "PolarityComponent.h"

void UTriggerChangeHealthComponent::ApplyEffect(AActor* Target, float EffectMagnitude)
{
	if (Target && Target->Implements<UHasHealth>())
	{
		if (Target && Target->Implements<UHasPolarity>() && GetOwner()->Implements<UHasPolarity>())
		{
			EPolarity TargetPolarity = IHasPolarity::Execute_GetPolarity(Target);
			EPolarity OwnPolarity = IHasPolarity::Execute_GetPolarity(GetOwner());
			if (OwnPolarity == TargetPolarity)
			{
				IHasHealth::Execute_TakeDamage(Target, -EffectMagnitude);
			}
			else
			{
				IHasHealth::Execute_TakeDamage(Target, EffectMagnitude);
			}
		}
	}
}
