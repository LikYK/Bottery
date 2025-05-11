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

EPolarity UPolarityComponent::GetPolarity_Implementation()
{
	return Polarity;
}

void UPolarityComponent::SetPolarity_Implementation(EPolarity NewPolarity)
{
	Polarity = NewPolarity;

	ColourComponent->ChangeColour(IPolarityInterface::Execute_GetPolarityColour(this, Polarity));
	PolarityDelegateWrapper->OnPolarityChanged.Broadcast(Polarity, IPolarityInterface::Execute_GetPolarityColour(this, Polarity));
}

void UPolarityComponent::SwitchPolarity_Implementation()
{
	if (Polarity == EPolarity::Positive)
	{
		IPolarityInterface::Execute_SetPolarity(this, EPolarity::Negative);
	}
	else 
	{
		IPolarityInterface::Execute_SetPolarity(this, EPolarity::Positive);
	}
}

FLinearColor UPolarityComponent::GetPolarityColour_Implementation(EPolarity TargetPolarity)
{
	if (TargetPolarity == EPolarity::Positive)
	{
		return PositiveColour;
	}
	else
	{
		return NegativeColour;
	}
}

UPolarityDelegateWrapper* UPolarityComponent::GetPolarityDelegateWrapper_Implementation()
{
	return PolarityDelegateWrapper;
}

void UPolarityComponent::SetRandomPolarity()
{
	bool bResult = FMath::RandBool();
	if (bResult)
	{
		IPolarityInterface::Execute_SetPolarity(this, EPolarity::Negative);
	}
	else
	{
		IPolarityInterface::Execute_SetPolarity(this, EPolarity::Positive);
	}
}

