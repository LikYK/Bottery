// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthDelegatesWrapper.h"
#include "HasHealth.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasHealth : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTERY_API IHasHealth
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	UHealthDelegatesWrapper* GetHealthDelegates();
};
