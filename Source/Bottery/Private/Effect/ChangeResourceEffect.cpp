// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/ChangeResourceEffect.h"
#include "ActorData/ResourceComponent.h"
#include "ActorData/StatComponent.h"
#include "ActorData/FlagComponent.h"
#include <Kismet/GameplayStatics.h>

void UChangeResourceEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UResourceComponent* TargetResourceComponent = Target->GetComponentByClass<UResourceComponent>();

	if (!TargetResourceComponent || !TargetResourceComponent->HasResource(TargetResource))
	{
		// Target has no target resource, this effect does not apply to it.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeResource Target return")));
		return;
	}

	// Get the required data from initiator
	UStatComponent* InitiatorStatComponent = Initiator->GetComponentByClass<UStatComponent>();
	UFlagComponent* InitiatorFlagComponent = Initiator->GetComponentByClass<UFlagComponent>();

	if ((!InitiatorStatComponent) || !InitiatorStatComponent->HasStat(EStatKey::Magnitude)
		|| (!InitiatorFlagComponent) || !InitiatorFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// The initiator is missing data needed to apply this effect, so this effect will not apply on any target, log a warning.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeResource initiator return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeResourceEffect ApplyEffect failed: Missing required component(s) or data in initiator, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// Increase or decrease target resource based on initiator's polarity
	bool InitiatorPolarity = InitiatorFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue();
	float Magnitude = InitiatorStatComponent->GetStat(EStatKey::Magnitude)->GetValue();

	UResource* TargetResourceObj = TargetResourceComponent->GetResource(TargetResource);
	if (InitiatorPolarity)
	{
		TargetResourceObj->ModifyValue(Magnitude);
		if (PositiveChangeSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				PositiveChangeSound,
				Initiator->GetActorLocation(),
				1.0f,
				1.0f,
				0.0f,
				nullptr
			);
		}
	}
	else
	{
		TargetResourceObj->ModifyValue(-Magnitude);
		if (NegativeChangeSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				NegativeChangeSound,
				Initiator->GetActorLocation(),
				1.0f,
				1.0f,
				0.0f,
				nullptr
			);
		}
	}

	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeResourceEffect end return, Polarity: %d, changeAmt: %f"), InitiatorPolarity, Magnitude));
}
