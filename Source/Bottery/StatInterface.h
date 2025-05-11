// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatKey.h"
#include "StatDelegateWrapper.h"
#include "StatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UStatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTERY_API IStatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	bool HasStat(EStatKey Key);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float GetStatBase(EStatKey Key);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float GetStatMax(EStatKey Key);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float GetStatMin(EStatKey Key);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	float GetStatValue(EStatKey Key);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	void SetStatValue(EStatKey Key, float NewSpeed);

	// Increases or decreases speed by a fixed amount for Steps times.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	void ModifyStat(EStatKey Key, float ChangeAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stats")
	UStatDelegateWrapper* GetStatDelegateWrapper(EStatKey Key);
};
