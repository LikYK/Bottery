// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/ChangeStatEffect.h"
#include "ActorData/StatComponent.h"
#include "ActorData/FlagComponent.h"

void UChangeStatEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UStatComponent* TargetStatComponent = Target->GetComponentByClass<UStatComponent>();

	if (!TargetStatComponent || !TargetStatComponent->HasStat(TargetStat))
	{
		// Target has no speed stat, this effect does not apply to it.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeStat Target return")));
		return;
	}

	// Get the required data from initiator
	UStatComponent* InitiatorStatComponent = Initiator->GetComponentByClass<UStatComponent>();
	UFlagComponent* InitiatorFlagComponent = Initiator->GetComponentByClass<UFlagComponent>();

	if (!InitiatorStatComponent || !InitiatorStatComponent->HasStat(EStatKey::Magnitude) 
		|| !InitiatorFlagComponent || !InitiatorFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// The initiator is missing data needed to apply this effect, so this effect will not apply on any target, log a warning.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeStat initiator return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeSpeedEffect ApplyEffect failed: Missing required component(s) or data in initiator, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// Based on initiator's polarity, increase or decrease target's speed by their base speed * initiator magnitude
	bool InitiatorPolarity = InitiatorFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue();
	float Magnitude = InitiatorStatComponent->GetStat(EStatKey::Magnitude)->GetValue();
	float BaseVal = TargetStatComponent->GetStat(TargetStat)->GetBaseValue();

	if (InitiatorPolarity) // True/Positive, increase the target's stat value
	{
		TargetStatComponent->GetStat(TargetStat)->ModifyValue(Magnitude * BaseVal);
	}
	else
	{
		TargetStatComponent->GetStat(TargetStat)->ModifyValue(-Magnitude * BaseVal);
	}
	
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeStatEffect end return, targetStat: %d, changeAmt: %f"), TargetStat, Magnitude * BaseVal));
}
