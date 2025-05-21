// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleSizeWithStatComponent.h"
#include "StatComponent.h"

// Sets default values for this component's properties
UScaleSizeWithStatComponent::UScaleSizeWithStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScaleSizeWithStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get root component as scaling target and get its original scale
	TargetComponent = GetOwner()->GetRootComponent();
	OriginalScale = TargetComponent->GetRelativeScale3D();
	
	// Check if target stat exists on owner
	UStatComponent* StatComponent = GetOwner()->GetComponentByClass<UStatComponent>();

	if (!StatComponent || !StatComponent->HasStat(TargetStatKey))
	{
		UE_LOG(LogTemp, Error, TEXT("ScaleSizeWithStatComponent failed to initialize, target stat is not found in owner."));
		return;
	}

	// Cache TargetStat for ScaleMultiplier's calculation in handler
	TargetStat = StatComponent->GetStat(TargetStatKey);

	// Bind handler that updates the ScaleMultiplier to target stat's OnstatChanged delegate
	TargetStat->OnStatChanged.AddUniqueDynamic(this, &UScaleSizeWithStatComponent::HandleTargetStatChange);

	// Update the actual scale of the target component automatically when ScaleMultiplier changes
	ScaleMultiplier->OnStatChanged.AddUniqueDynamic(this, &UScaleSizeWithStatComponent::UpdateScale);
}


// Called every frame
void UScaleSizeWithStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UScaleSizeWithStatComponent::UpdateScale(float NewTargetValue, float BaseTargetValue)
{
	TargetComponent->SetRelativeScale3D(OriginalScale * NewTargetValue);
}

float UScaleSizeWithStatComponent::GetScale()
{
	return ScaleMultiplier->GetValue();
}

void UScaleSizeWithStatComponent::HandleTargetStatChange(float NewTargetValue, float BaseTargetValue)
{
	float TargetMin = TargetStat->GetMinValue();
	float TargetMax = TargetStat->GetMaxValue();
	float ScaleMin = ScaleMultiplier->GetMinValue();
	float ScaleMax = ScaleMultiplier->GetMaxValue();
	float ScaleBase = ScaleMultiplier->GetBaseValue();

	// GetMappedRangeValueClamped performs inverse-lerp with 3rd and 1st parameter, and performs lerp with the result and the 2nd parameter
	if (NewTargetValue < BaseTargetValue)
	{
		ScaleMultiplier->SetValue(FMath::GetMappedRangeValueClamped(
			FVector2D(TargetMin, BaseTargetValue),
			FVector2D(ScaleMin, ScaleBase),
			NewTargetValue
		));
	}
	else
	{
		ScaleMultiplier->SetValue(FMath::GetMappedRangeValueClamped(
			FVector2D(BaseTargetValue, TargetMax),
			FVector2D(ScaleBase, ScaleMax),
			NewTargetValue
		));
	}

}