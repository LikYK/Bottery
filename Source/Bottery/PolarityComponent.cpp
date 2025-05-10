// Fill out your copyright notice in the Description page of Project Settings.


#include "PolarityComponent.h"

// Sets default values for this component's properties
UPolarityComponent::UPolarityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PositiveColour = FLinearColor::Blue;
	NegativeColour = FLinearColor::Red;
	PolarityDelegateWrapper = CreateDefaultSubobject<UPolarityDelegateWrapper>(TEXT("PolarityDelegateWrapper"));
	ColourComponent = CreateDefaultSubobject<UColourComponent>(TEXT("ColourComponent"));
}


// Called when the game starts
void UPolarityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ColourComponent->IsReady())
	{
		SetRandomPolarity();
	}
	else 
	{
		ColourComponent->OnColourReady.AddUniqueDynamic(this, &UPolarityComponent::SetRandomPolarity);
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

	ColourComponent->ChangeColour(GetPolarityColour());
	PolarityDelegateWrapper->OnPolarityChanged.Broadcast(Polarity, GetPolarityColour());
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

FLinearColor UPolarityComponent::GetPolarityColour()
{
	if (Polarity == EPolarity::Positive)
	{
		return PositiveColour;
	}
	else
	{
		return NegativeColour;
	}
}

void UPolarityComponent::SetRandomPolarity()
{
	bool bResult = FMath::RandBool();
	if (bResult)
	{
		SetPolarity(EPolarity::Negative);
	}
	else
	{
		SetPolarity(EPolarity::Positive);
	}
}

