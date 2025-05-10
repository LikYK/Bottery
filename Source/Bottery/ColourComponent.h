// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Polarity.h"
#include "ColourComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnColourReadySignature);

USTRUCT(BlueprintType)
struct FMaterialParamInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	int32 MaterialIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	FName ParameterName;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UColourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColourComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Colour")
	void ChangeColour(FLinearColor Colour);

	UFUNCTION(BlueprintCallable, Category = "Colour")
	bool IsReady();

	UPROPERTY(BlueprintAssignable, Category = "Colour")
	FOnColourReadySignature OnColourReady;

protected:
	// List of materials (indexes) and their parameters (names) that need to be modified
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	TArray<FMaterialParamInfo> ParametersToChange;

	// For each material involved, a dynamic instance is created and stored
	TMap<int32, UMaterialInstanceDynamic*> DynamicMaterials;

	bool isReady = false;
};
