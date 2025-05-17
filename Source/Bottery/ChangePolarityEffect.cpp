// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangePolarityEffect.h"
#include "FlagComponent.h"

void UChangePolarityEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UFlagComponent* TargetFlagComponent = Target->GetComponentByClass<UFlagComponent>();

	if (!TargetFlagComponent || !TargetFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// Target has no polarity, this effect does not apply to it.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangePolarity Target return")));
		return;
	}

	// Apply effect
	// Switch target's polarity
	TargetFlagComponent->GetFlag(EFlagKey::Polarity)->SwitchValue();

	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangePolarityEffect end return, newPolarity: %d"), TargetFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue()));
}
