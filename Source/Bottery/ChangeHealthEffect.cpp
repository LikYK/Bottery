// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeHealthEffect.h"
#include "ResourceComponent.h"
#include "StatComponent.h"
#include "FlagComponent.h"
#include <Kismet/GameplayStatics.h>

void UChangeHealthEffect::ApplyEffect(AActor* Initiator, AActor* Target)
{
	// Check if this effect applies to the target
	UResourceComponent* TargetResourceComponent = Target->GetComponentByClass<UResourceComponent>();
	UStatComponent* TargetStatComponent = Target->GetComponentByClass<UStatComponent>();
	UFlagComponent* TargetFlagComponent = Target->GetComponentByClass<UFlagComponent>();

	if (!TargetResourceComponent || !TargetResourceComponent->HasResource(EResourceKey::Health)
		|| !TargetStatComponent || !TargetStatComponent->HasStat(EStatKey::Magnitude)
		|| !TargetFlagComponent || !TargetFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// Target does not have all the data needed, this effect does not apply to it.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealth Target return")));
		return;
	}

	// Get the required data from initiator
	UStatComponent* InitiatorStatComponent = Initiator->GetComponentByClass<UStatComponent>();
	UFlagComponent* InitiatorFlagComponent = Initiator->GetComponentByClass<UFlagComponent>();

	if ((!InitiatorStatComponent) || !InitiatorStatComponent->HasStat(EStatKey::Magnitude) 
		|| (!InitiatorFlagComponent) || !InitiatorFlagComponent->HasFlag(EFlagKey::Polarity))
	{
		// The initiator is missing data needed to apply this effect, so this effect will not apply on any target, log an error.
		//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealth initiator return")));
		UE_LOG(LogTemp, Error, TEXT("ChangeHealthEffect ApplyEffect failed: Missing required component(s) or data in initiator, this effect will fail to apply on any target!"));
		return;
	}

	// Apply effect
	// If target and initiator have the same polarity, heal target, else damage it
	bool InitiatorPolarity = InitiatorFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue();
	float InitiatorMagnitude = InitiatorStatComponent->GetStat(EStatKey::Magnitude)->GetValue();
	bool TargetPolarity = TargetFlagComponent->GetFlag(EFlagKey::Polarity)->GetValue();
	float TargetMagnitude = TargetStatComponent->GetStat(EStatKey::Magnitude)->GetValue();

	UResource* TargetHealth = TargetResourceComponent->GetResource(EResourceKey::Health);
	if (InitiatorPolarity == TargetPolarity)
	{
		TargetHealth->ModifyValue(InitiatorMagnitude * TargetMagnitude);
		if (HealSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HealSound,
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
		TargetHealth->ModifyValue(-InitiatorMagnitude * TargetMagnitude);
		if (DamageSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				DamageSound,
				Initiator->GetActorLocation(),
				1.0f,
				1.0f,
				0.0f,
				nullptr
			);
		}
	}

	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ChangeHealthEffect end return, samePolarity: %d, changeAmt: %f"), InitiatorPolarity == TargetPolarity, InitiatorMagnitude));
}
