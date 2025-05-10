// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Polarity.h"
#include "PolarityDelegateWrapper.h"
#include "HasPolarity.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasPolarity : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTERY_API IHasPolarity
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Polarity")
	EPolarity GetPolarity();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Polarity")
	void SetPolarity(EPolarity NewPolarity);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Polarity")
	void SwitchPolarity();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Polarity")
	FLinearColor GetPolarityColour();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Polarity")
	UPolarityDelegateWrapper* GetPolarityDelegateWrapper();
};
