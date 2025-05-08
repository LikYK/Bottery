// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatDelegateWrapper.h"
#include "HasSpeed.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasSpeed : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTERY_API IHasSpeed
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	float GetBaseSpeed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	float GetMaxSpeed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	float GetMinSpeed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	void SetSpeed(float NewSpeed);

	// Increases or decreases speed by a fixed amount for Steps times.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	void ModifySpeed(float ChangeAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Speed")
	UStatDelegateWrapper* GetSpeedDelegateWrapper();
};
