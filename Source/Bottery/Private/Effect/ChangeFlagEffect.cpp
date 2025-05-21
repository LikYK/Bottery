// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/ChangeFlagEffect.h"
#include "ActorData/FlagComponent.h"

void UChangeFlagEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UFlagComponent* TargetFlagComponent = Target->GetComponentByClass<UFlagComponent>();

	if (!TargetFlagComponent || !TargetFlagComponent->HasFlag(TargetFlag))
	{
		// Target has no target flag, this effect does not apply to it.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeFlag Target return")));
		return;
	}

	// Apply effect
	// Switch target flag
	TargetFlagComponent->GetFlag(TargetFlag)->SwitchValue();

	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeFlagEffect end return, newValue: %d"), TargetFlagComponent->GetFlag(TargetFlag)->GetValue()));
}
