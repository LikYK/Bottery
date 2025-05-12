// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangePolarityEffect.h"
#include "PolarityInterface.h"

void UChangePolarityEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	TArray<UActorComponent*> TargetPolarityComponents = Target->GetComponentsByInterface(UPolarityInterface::StaticClass());

	UActorComponent* TargetPolarityInterface = nullptr;

	if (TargetPolarityComponents.Num() > 0)
		TargetPolarityInterface = TargetPolarityComponents[0];

	if (!TargetPolarityInterface)
	{
		// Target has no polarity, this effect does not apply to it.
		if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangePolarity Target return")));
		return;
	}

	// Apply effect
	// Switch target's polarity
	IPolarityInterface::Execute_SwitchPolarity(TargetPolarityInterface);

	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangePolarityEffect end return, newPolarity: %d"), IPolarityInterface::Execute_GetPolarity(TargetPolarityInterface)));
}
