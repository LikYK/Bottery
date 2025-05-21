// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorData/Stat.h"

UStat::UStat()
{
}

void UStat::PostInitProperties()
{
	Super::PostInitProperties();

	// After properties are loaded from defaults, set current value = base value
	// This works when the UStat is added in C++ through CreateDefaultObject<>
	InitValue();
}

void UStat::PostLoad()
{
	Super::PostLoad();

	// Set current value = base value for instances added through blueprints/editor
	InitValue();
}

float UStat::GetBaseValue() const
{
	return BaseValue;
}

float UStat::GetMaxValue() const
{
	return MaxValue;
}

float UStat::GetMinValue() const
{
	return MinValue;
}

float UStat::GetValue() const
{
	return Value;
}

void UStat::SetValue(float NewValue)
{
	Value = FMath::Clamp(NewValue, MinValue, MaxValue);
	OnStatChanged.Broadcast(Value, BaseValue);
}

void UStat::ModifyValue(float ChangeAmount)
{
	SetValue(Value + ChangeAmount);
}

void UStat::InitValue()
{
	Value = BaseValue;
}
