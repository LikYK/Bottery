// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeColourWithFlagComponent.h"
#include "FlagComponent.h"

// Sets default values for this component's properties
UChangeColourWithFlagComponent::UChangeColourWithFlagComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TrueColour = FLinearColor::Blue;
	FalseColour = FLinearColor::Red;
	ColourComponent = CreateDefaultSubobject<UColourComponent>(TEXT("ChangeWithFlagColour"));
}


// Called when the game starts
void UChangeColourWithFlagComponent::BeginPlay()
{
	Super::BeginPlay();

	// Check if target flag exists on owner
	UFlagComponent* FlagComponent = GetOwner()->GetComponentByClass<UFlagComponent>();

	if (!FlagComponent || !FlagComponent->HasFlag(TargetFlagKey))
	{
		UE_LOG(LogTemp, Error, TEXT("ChangeColourWithFlagComponent failed to initialize, target flag is not found in owner."));
		return;
	}
	TargetFlag = FlagComponent->GetFlag(TargetFlagKey);

	if (ColourComponent->IsReady())
	{
		ChangeColourWithFlag();
	}
	else
	{
		ColourComponent->OnColourReady.AddUniqueDynamic(this, &UChangeColourWithFlagComponent::ChangeColourWithFlag);
	}

	TargetFlag->OnFlagChanged.AddUniqueDynamic(this, &UChangeColourWithFlagComponent::HandleTargetFlagChange);
}


// Called every frame
void UChangeColourWithFlagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UChangeColourWithFlagComponent::HandleTargetFlagChange(bool bNewTargetValue)
{
	if (ColourComponent->IsReady())
	{
		ColourComponent->ChangeColour(bNewTargetValue ? TrueColour : FalseColour);
	}
}

void UChangeColourWithFlagComponent::ChangeColourWithFlag()
{
	ColourComponent->ChangeColour(TargetFlag->GetValue() ? TrueColour : FalseColour);
}

FLinearColor UChangeColourWithFlagComponent::GetColour(bool bPolarity)
{
	return bPolarity ? TrueColour : FalseColour;
}

