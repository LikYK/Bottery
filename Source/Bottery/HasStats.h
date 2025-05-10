// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatDelegateWrapper.h"
#include "StatKey.h"
#include "HasStats.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasStats : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTERY_API IHasStats
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	bool HasStat(EStatKey Key);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	float GetStatBase(EStatKey Key);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	float GetStatMax(EStatKey Key);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	float GetStatMin(EStatKey Key);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	float GetStatValue(EStatKey Key);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	void SetStatValue(EStatKey Key, float NewSpeed);

	// Increases or decreases speed by a fixed amount for Steps times.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	void ModifyStat(EStatKey Key, float ChangeAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Stats")
	UStatDelegateWrapper* GetStatDelegateWrapper(EStatKey Key);
};
