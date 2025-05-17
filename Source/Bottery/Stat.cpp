// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat.h"

UStat::UStat()
{
	DelegateWrapper = CreateDefaultSubobject<UStatDelegateWrapper>(TEXT("DelegateWrapper"));
}

void UStat::PostInitProperties()
{
	Super::PostInitProperties();

	// After properties are loaded from defaults, set current value = base value
	// This only works when the component containing UStat is added in C++ through CreateDefaultObject<>
	Value = BaseValue;
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("postinit, val: %f, %f"), Value, BaseValue));
}

void UStat::PostDuplicate(bool bDuplicateForPIE)
{
	Super::PostDuplicate(bDuplicateForPIE);

	// Set current value = base value for UStat added in Blueprint
	Value = BaseValue;
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("postduplicate, val: %f, %f"), Value, BaseValue));
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
	DelegateWrapper->OnStatChanged.Broadcast(Value, BaseValue);
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
