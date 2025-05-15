// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangePolarityEffect.h"
#include "PolarityComponent.h"

void UChangePolarityEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UPolarityComponent* TargetPolarityComponent = Target->GetComponentByClass<UPolarityComponent>();

	if (!TargetPolarityComponent)
	{
		// Target has no polarity, this effect does not apply to it.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangePolarity Target return")));
		return;
	}

	// Apply effect
	// Switch target's polarity
	TargetPolarityComponent->SwitchPolarity();

	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangePolarityEffect end return, newPolarity: %d"), TargetPolarityComponent->GetPolarity()));
}
