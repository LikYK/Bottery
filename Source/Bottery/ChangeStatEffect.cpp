// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeStatEffect.h"
#include "StatComponent.h"
#include "PolarityComponent.h"

void UChangeStatEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UStatComponent* TargetStatComponent = Target->GetComponentByClass<UStatComponent>();

	if (!TargetStatComponent || !TargetStatComponent->HasStat(TargetStat))
	{
		// Target has no speed stat, this effect does not apply to it.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeStat Target return")));
		return;
	}

	// Get the required data from initiator
	UStatComponent* InitiatorStatComponent = Initiator->GetComponentByClass<UStatComponent>();
	UPolarityComponent* InitiatorPolarityComponent = Initiator->GetComponentByClass<UPolarityComponent>();

	if ((!InitiatorStatComponent) || (!InitiatorStatComponent->HasStat(EStatKey::Magnitude)) || (!InitiatorPolarityComponent))
	{
		// The initiator is missing data needed to apply this effect, so this effect will not apply on any target, log a warning.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeStat initiator return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeSpeedEffect ApplyEffect failed: Missing required component(s) or data in initiator, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// Based on initiator's polarity, increase or decrease target's speed by their base speed * initiator magnitude
	EPolarity InitiatorPolarity = InitiatorPolarityComponent->GetPolarity();
	float Magnitude = InitiatorStatComponent->GetStatValue(EStatKey::Magnitude);
	float BaseVal = TargetStatComponent->GetStatBase(TargetStat);

	if (InitiatorPolarity == EPolarity::Positive)
	{
		TargetStatComponent->ModifyStat(TargetStat, Magnitude * BaseVal);
	}
	else
	{
		TargetStatComponent->ModifyStat(TargetStat, -Magnitude * BaseVal);
	}
	
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeStatEffect end return, targetStat: %d, changeAmt: %f"), TargetStat, Magnitude * BaseVal));
}
