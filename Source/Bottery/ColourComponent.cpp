// Fill out your copyright notice in the Description page of Project Settings.


#include "ColourComponent.h"

// Sets default values for this component's properties
UColourComponent::UColourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UColourComponent::BeginPlay()
{
	Super::BeginPlay();

	UMeshComponent* Mesh = GetOwner()->FindComponentByClass<UMeshComponent>();
	if (!Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("ColourComponent init failed: No mesh found."));
		return;
	}

	for (const FMaterialParamInfo& Info : ParametersToChange)
	{
		// Only create one dynamic instance for each material
		if (!DynamicMaterials.Contains(Info.MaterialIndex))
		{
			UMaterialInterface* ParentMat = Mesh->GetMaterial(Info.MaterialIndex);
			if (ParentMat)
			{
				UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(ParentMat, this);

				Mesh->SetMaterial(Info.MaterialIndex, MID);
				DynamicMaterials.Add(Info.MaterialIndex, MID);
			}
		}
	}

	isReady = true;
	OnColourReady.Broadcast();
}

// Called every frame
void UColourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UColourComponent::ChangeColour(FLinearColor Colour)
{
	for (const FMaterialParamInfo& Info : ParametersToChange)
	{
		if (DynamicMaterials.Contains(Info.MaterialIndex))
		{
			if (UMaterialInstanceDynamic* MID = DynamicMaterials[Info.MaterialIndex])
			{
				MID->SetVectorParameterValue(Info.ParameterName, Colour);
			}
		}
	}
}

bool UColourComponent::IsReady()
{
	return isReady;
}
