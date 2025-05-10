// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedOrb.h"

ASpeedOrb::ASpeedOrb()
{
	// Add a default stat component
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("Stats"));

	// Add a default polarity component
	PolarityComponent = CreateDefaultSubobject<UPolarityComponent>(TEXT("Polarity"));
}

bool ASpeedOrb::HasStat_Implementation(EStatKey Key)
{
	return StatComponent->HasStat(Key);
}

float ASpeedOrb::GetStatBase_Implementation(EStatKey Key)
{
	return StatComponent->GetStatBase(Key);
}

float ASpeedOrb::GetStatMax_Implementation(EStatKey Key)
{
	return StatComponent->GetStatMax(Key);
}

float ASpeedOrb::GetStatMin_Implementation(EStatKey Key)
{
	return StatComponent->GetStatMin(Key);
}

float ASpeedOrb::GetStatValue_Implementation(EStatKey Key)
{
	return StatComponent->GetStatValue(Key);
}

void ASpeedOrb::SetStatValue_Implementation(EStatKey Key, float NewValue)
{
	StatComponent->SetStatValue(Key, NewValue);
}

void ASpeedOrb::ModifyStat_Implementation(EStatKey Key, float ChangeAmount)
{
	StatComponent->ModifyStat(Key, ChangeAmount);
}

UStatDelegateWrapper* ASpeedOrb::GetStatDelegateWrapper_Implementation(EStatKey Key)
{
	return StatComponent->GetStatDelegateWrapper(Key);
}

EPolarity ASpeedOrb::GetPolarity_Implementation()
{
	return PolarityComponent->GetPolarity();
}

void ASpeedOrb::SetPolarity_Implementation(EPolarity NewPolarity)
{
	PolarityComponent->SetPolarity(NewPolarity);
}

void ASpeedOrb::SwitchPolarity_Implementation()
{
	PolarityComponent->SwitchPolarity();
}

FLinearColor ASpeedOrb::GetPolarityColour_Implementation()
{
	return PolarityComponent->GetPolarityColour();
}

UPolarityDelegateWrapper* ASpeedOrb::GetPolarityDelegateWrapper_Implementation()
{
	return PolarityComponent->PolarityDelegateWrapper;
}
