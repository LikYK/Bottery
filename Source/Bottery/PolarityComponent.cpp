// Fill out your copyright notice in the Description page of Project Settings.


#include "PolarityComponent.h"

// Sets default values for this component's properties
UPolarityComponent::UPolarityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PositiveColor = FLinearColor::Blue;
	NegativeColor = FLinearColor::Red;
}


// Called when the game starts
void UPolarityComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set a random polarity
	float bResult = FMath::RandBool();
	if (bResult)
	{
		SetPolarity(EPolarity::Negative);
	}
	else 
	{
		SetPolarity(EPolarity::Positive);
	}
}


// Called every frame
void UPolarityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EPolarity UPolarityComponent::GetPolarity()
{
	return Polarity;
}

void UPolarityComponent::SetPolarity(EPolarity NewPolarity)
{
	Polarity = NewPolarity;

	OnPolarityChanged.Broadcast(Polarity, GetPolarityColor());
}

void UPolarityComponent::SwitchPolarity()
{
	if (Polarity == EPolarity::Positive)
	{
		SetPolarity(EPolarity::Negative);
	}
	else 
	{
		SetPolarity(EPolarity::Positive);
	}
}

FLinearColor UPolarityComponent::GetPolarityColor()
{
	if (Polarity == EPolarity::Positive)
	{
		return PositiveColor;
	}
	else
	{
		return NegativeColor;
	}
}

