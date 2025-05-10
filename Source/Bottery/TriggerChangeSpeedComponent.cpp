// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerChangeSpeedComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BotteryCharacter.h"
#include "PolarityComponent.h"

void UTriggerChangeSpeedComponent::ApplyEffect(AActor* Target, float EffectMagnitude)
{
	if (Target && Target->Implements<UHasStats>() && IHasStats::Execute_HasStat(Target, EStatKey::Speed))
	{
		if (UPolarityComponent* PolarityComponent = GetOwner()->GetComponentByClass<UPolarityComponent>())
		{
			EPolarity Polarity = PolarityComponent->GetPolarity();
			float BaseVal = IHasStats::Execute_GetStatBase(Target, EStatKey::Speed);

			if (Polarity == EPolarity::Positive)
			{
				IHasStats::Execute_ModifyStat(Target, EStatKey::Speed, EffectMagnitude * BaseVal);
				//Character->GetCharacterMovement()->MaxWalkSpeed += EffectMagnitude;
			}
			else 
			{
				IHasStats::Execute_ModifyStat(Target, EStatKey::Speed, -EffectMagnitude * BaseVal);
				//Character->GetCharacterMovement()->MaxWalkSpeed -= EffectMagnitude;
			}
			GetOwner()->Destroy();
		}
	}
}