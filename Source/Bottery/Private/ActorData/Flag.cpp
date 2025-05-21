// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorData/Flag.h"

UFlag::UFlag()
{
}

void UFlag::PostInitProperties()
{
	Super::PostInitProperties();

	// After properties are loaded from defaults, set current value = base value
	// This works when the UStat is added in C++ through CreateDefaultObject<>
	InitValue();
}

void UFlag::PostLoad()
{
	Super::PostLoad();

	// Set current value = base value for instances added through blueprints/editor
	InitValue();
}

bool UFlag::GetBaseValue() const
{
	return bBaseValue;
}

bool UFlag::GetValue() const
{
	return bValue;
}

void UFlag::SetValue(bool bNewValue)
{
	bValue = bNewValue;
	OnFlagChanged.Broadcast(bValue);
}

void UFlag::SwitchValue()
{
	SetValue(!bValue);
}

void UFlag::RandomizeValue()
{
	SetValue(FMath::RandBool());
}

void UFlag::InitValue()
{
	if (bRandomBaseValue)
	{
		bBaseValue = FMath::RandBool();
	}
	bValue = bBaseValue;
}
