// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/DamageEffect.h"
#include "ActorData/ResourceComponent.h"
#include "ActorData/StatComponent.h"
#include "ActorData/FlagComponent.h"

void UDamageEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UResourceComponent* TargetResourceComponent = Target->GetComponentByClass<UResourceComponent>();
	UStatComponent* TargetStatComponent = Target->GetComponentByClass<UStatComponent>();

	if (!TargetResourceComponent || !TargetResourceComponent->HasResource(EResourceKey::Health)
		|| !TargetStatComponent || !TargetStatComponent->HasStat(EStatKey::Magnitude))
	{
		// Target does not have all the data needed, this effect does not apply to it.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Damage Target return")));
		return;
	}

	// Get the required data from initiator
	UStatComponent* InitiatorStatComponent = Initiator->GetComponentByClass<UStatComponent>();
	UFlagComponent* InitiatorFlagComponent = Initiator->GetComponentByClass<UFlagComponent>();

	if ((!InitiatorStatComponent) || (!InitiatorStatComponent->HasStat(EStatKey::Magnitude)))
	{
		// The initiator is missing data needed to apply this effect, so this effect will not apply on any target, log an error.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Damage initiator return")));
		UE_LOG(LogTemp, Error, TEXT("DamageEffect ApplyEffect failed: Missing required component(s) or data in initiator, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// Damage target
	float InitiatorMagnitude = InitiatorStatComponent->GetStat(EStatKey::Magnitude)->GetValue();
	float TargetMagnitude = TargetStatComponent->GetStat(EStatKey::Magnitude)->GetValue();

	UResource* TargetHealth = TargetResourceComponent->GetResource(EResourceKey::Health);
	TargetHealth->ModifyValue(-InitiatorMagnitude * TargetMagnitude);
}
