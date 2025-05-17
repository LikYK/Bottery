// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag.h"

UFlag::UFlag()
{
	DelegateWrapper = CreateDefaultSubobject<UFlagDelegateWrapper>(TEXT("DelegateWrapper"));
}

void UFlag::PostInitProperties()
{
	Super::PostInitProperties();

	InitValue();
}

void UFlag::PostDuplicate(bool bDuplicateForPIE)
{
	Super::PostDuplicate(bDuplicateForPIE);

	InitValue();
}

bool UFlag::GetBaseValue()
{
	return bBaseValue;
}

bool UFlag::GetValue()
{
	return bValue;
}

void UFlag::SetValue(bool bNewValue)
{
	bValue = bNewValue;
	DelegateWrapper->OnFlagChanged.Broadcast(bValue);
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
