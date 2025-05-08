// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HealthDelegateWrapper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, MaxHealth);

// This is a wrapper class that contains delegates related to health and damage
// Wrapping delegates allow them to be passed to blueprints for binding
// and also allow them to be declared in interfaces as function return type
UCLASS()
class BOTTERY_API UHealthDelegateWrapper : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category =  "Delegates")
	FOnHealthChangedSignature OnHealthChanged;
};
