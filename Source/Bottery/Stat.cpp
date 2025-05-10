// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"

UStat::UStat()
{
	StatDelegateWrapper = CreateDefaultSubobject<UStatDelegateWrapper>(TEXT("StatDelegateWrapper"));
}

void UStat::PostInitProperties()
{
	Super::PostInitProperties();

	// After properties are loaded from defaults, set current value = base value
	Value = BaseValue;
}

float UStat::GetBaseValue()
{
	return BaseValue;
}

float UStat::GetMaxValue()
{
	return MaxValue;
}

float UStat::GetMinValue()
{
	return MinValue;
}

float UStat::GetValue()
{
	return Value;
}

void UStat::SetValue(float NewValue)
{
	Value = FMath::Clamp(NewValue, MinValue, MaxValue);
	StatDelegateWrapper->OnStatChanged.Broadcast(Value, BaseValue);
}

void UStat::ModifyValue(float ChangeAmount)
{
	SetValue(Value + ChangeAmount);
}

//void UStat::SetBase(float Base)
//{
//	BaseStat = Base;
//}
//
//float UStat::GetMaxMultiplier()
//{
//	return MaxMultiplier;
//}
//
//float UStat::GetMinMultiplier()
//{
//	return MinMultiplier;
//}
//
//float UStat::GetMultiplier()
//{
//	return Multiplier;
//}
//
//void UStat::SetMultiplier(float NewMultiplier)
//{
//	Multiplier = NewMultiplier;
//
//	StatDelegateWrapper->OnStatChanged.Broadcast(Multiplier * BaseStat, BaseStat);
//}
//
//float UStat::GetMultiplierStep()
//{
//	return MultiplierStep;
//}
//
//void UStat::StepMultiplier(float Steps)
//{
//	SetMultiplier(Multiplier + MultiplierStep * Steps);
//}
