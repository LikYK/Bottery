// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeHealthEffect.h"
#include "HealthComponent.h"
#include "StatComponent.h"
#include "FlagComponent.h"

void UChangeHealthEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UHealthComponent* TargetHealthComponent = Target->GetComponentByClass<UHealthComponent>();
	UFlagComponent* TargetFlagComponent = Target->GetComponentByClass<UFlagComponent>();

	if (!TargetHealthComponent || !TargetFlagComponent || !TargetFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// Target has no health or polarity (needed to decide heal or damage), this effect does not apply to it.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealth Target return")));
		return;
	}

	// Get the required data from initiator
	UStatComponent* InitiatorStatComponent = Initiator->GetComponentByClass<UStatComponent>();
	UFlagComponent* InitiatorFlagComponent = Initiator->GetComponentByClass<UFlagComponent>();

	if ((!InitiatorStatComponent) || !InitiatorStatComponent->HasStat(EStatKey::Magnitude) 
		|| (!InitiatorFlagComponent) || !InitiatorFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// The initiator is missing data needed to apply this effect, so this effect will not apply on any target, log a warning.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealth initiator return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeHealthEffect ApplyEffect failed: Missing required component(s) or data in initiator, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// If target and initiator have the same polarity, heal target, else damage it
	bool InitiatorPolarity = InitiatorFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue();
	bool TargetPolarity = TargetFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue();
	float Magnitude = InitiatorStatComponent->GetStat(EStatKey::Magnitude)->GetValue();

	if (InitiatorPolarity == TargetPolarity)
	{
		TargetHealthComponent->TakeDamage(-Magnitude); // Negative damage means healing
	}
	else
	{
		TargetHealthComponent->TakeDamage(Magnitude);
	}

	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealthEffect end return, samePolarity: %d, changeAmt: %f"), InitiatorPolarity == TargetPolarity, Magnitude));
}
