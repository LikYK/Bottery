// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeHealthEffect.h"
#include "HealthInterface.h"
#include "StatInterface.h"
#include "PolarityInterface.h"

void UChangeHealthEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	TArray<UActorComponent*> TargetHealthComponents = Target->GetComponentsByInterface(UHealthInterface::StaticClass());
	TArray<UActorComponent*> TargetPolarityComponents = Target->GetComponentsByInterface(UPolarityInterface::StaticClass());

	UActorComponent* TargetHealthInterface = nullptr;
	UActorComponent* TargetPolarityInterface = nullptr;

	if (TargetHealthComponents.Num() > 0)
		TargetHealthInterface = TargetHealthComponents[0];
	if (TargetPolarityComponents.Num() > 0)
		TargetPolarityInterface = TargetPolarityComponents[0];

	if (!TargetHealthInterface || !TargetPolarityInterface)
	{
		// Target has no health or polarity (needed to decide heal or damage), this effect does not apply to it.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealth Target return")));
		return;
	}

	// Get the required interfaces from owner
	TArray<UActorComponent*> InitiatorStatComponents = Initiator->GetComponentsByInterface(UStatInterface::StaticClass());
	TArray<UActorComponent*> InitiatorPolarityComponents = Initiator->GetComponentsByInterface(UPolarityInterface::StaticClass());

	UActorComponent* InitiatorStatInterface = nullptr;
	UActorComponent* InitiatorPolarityInterface = nullptr;

	if (InitiatorStatComponents.Num() > 0)
		InitiatorStatInterface = InitiatorStatComponents[0];
	if (InitiatorPolarityComponents.Num() > 0)
		InitiatorPolarityInterface = InitiatorPolarityComponents[0];

	if ((!InitiatorStatInterface) || (!IStatInterface::Execute_HasStat(InitiatorStatInterface, EStatKey::Magnitude)) || (!InitiatorPolarityInterface))
	{
		// The owner is missing data needed to apply this effect, so this effect will not apply on any target, log a warning.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealth owner return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeHealthEffect ApplyEffect failed: Missing required component(s) or data in owner, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// If target and self have the same polarity, heal target, else damage it
	EPolarity SelfPolarity = IPolarityInterface::Execute_GetPolarity(InitiatorPolarityInterface);
	EPolarity TargetPolarity = IPolarityInterface::Execute_GetPolarity(TargetPolarityInterface);
	float Magnitude = IStatInterface::Execute_GetStatValue(InitiatorStatInterface, EStatKey::Magnitude);

	if (SelfPolarity == TargetPolarity)
	{
		IHealthInterface::Execute_TakeDamage(TargetHealthInterface, -Magnitude); // Negative damage means healing
	}
	else
	{
		IHealthInterface::Execute_TakeDamage(TargetHealthInterface, Magnitude);
	}

	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealthEffect end return, samePolarity: %d, changeAmt: %f"), SelfPolarity == TargetPolarity, Magnitude));
}
