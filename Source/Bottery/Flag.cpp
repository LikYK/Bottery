// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag.h"

UFlag::UFlag()
{
}

void UFlag::PostInitProperties()
{
	Super::PostInitProperties();

	InitValue();
}

//void UFlag::PostDuplicate(bool bDuplicateForPIE)
//{
//	Super::PostDuplicate(bDuplicateForPIE);
//
//	InitValue();
//}

void UFlag::PostLoad()
{
	Super::PostLoad();

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
	SetValue(bBaseValue);
}
