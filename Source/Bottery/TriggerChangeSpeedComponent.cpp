// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeSpeedComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BotteryCharacter.h"
#include "HasSpeed.h"
#include "PolarityComponent.h"

void UTriggerChangeSpeedComponent::ApplyEffect(AActor* Target, float EffectMagnitude)
{
	if (Target && Target->Implements<UHasSpeed>())
	{
		if (UPolarityComponent* PolarityComponent = GetOwner()->GetComponentByClass<UPolarityComponent>())
		{
			EPolarity Polarity = PolarityComponent->GetPolarity();
			float BaseVal = IHasSpeed::Execute_GetBaseSpeed(Target);

			if (Polarity == EPolarity::Positive)
			{
				IHasSpeed::Execute_ModifySpeed(Target, EffectMagnitude * BaseVal);
				//Character->GetCharacterMovement()->MaxWalkSpeed += EffectMagnitude;
			}
			else 
			{
				IHasSpeed::Execute_ModifySpeed(Target, -EffectMagnitude * BaseVal);
				//Character->GetCharacterMovement()->MaxWalkSpeed -= EffectMagnitude;
			}
			GetOwner()->Destroy();
		}
	}
}