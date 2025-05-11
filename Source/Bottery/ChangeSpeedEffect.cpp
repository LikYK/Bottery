// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSpeedEffect.h"
#include "StatInterface.h"
#include "PolarityInterface.h"

void UChangeSpeedEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	TArray<UActorComponent*> TargetStatComponents = Target->GetComponentsByInterface(UStatInterface::StaticClass());
	UActorComponent* TargetStatInterface = nullptr;

	if (TargetStatComponents.Num() > 0)
		TargetStatInterface = TargetStatComponents[0];

	if (!TargetStatInterface || !IStatInterface::Execute_HasStat(TargetStatInterface, EStatKey::Speed))
	{
		// Target has no speed stat, this effect does not apply to it.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Target return")));
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
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("owner return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeSpeedEffect ApplyEffect failed: Missing required component(s) or data in owner, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// Based on owner's polarity, increase or decrease target's speed by their base speed * owner magnitude
	EPolarity SelfPolarity = IPolarityInterface::Execute_GetPolarity(InitiatorPolarityInterface);
	float Magnitude = IStatInterface::Execute_GetStatValue(InitiatorStatInterface, EStatKey::Magnitude);
	float BaseVal = IStatInterface::Execute_GetStatBase(TargetStatInterface, EStatKey::Speed);

	if (SelfPolarity == EPolarity::Positive)
	{
		IStatInterface::Execute_ModifyStat(TargetStatInterface, EStatKey::Speed, Magnitude * BaseVal);
	}
	else
	{
		IStatInterface::Execute_ModifyStat(TargetStatInterface, EStatKey::Speed, -Magnitude * BaseVal);
	}
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Func end return, implements: %d"), TargetStatInterface->Implements<UStatInterface>()));
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Func end return, baseval: %f"), Magnitude * BaseVal));
}
