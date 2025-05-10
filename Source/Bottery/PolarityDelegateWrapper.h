// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Polarity.h"
#include "PolarityDelegateWrapper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPolarityChangedSignature, EPolarity, Polarity, FLinearColor, Colour);

// This is a wrapper class that contains delegates related to polarity
// Wrapping delegates allow them to be passed to blueprints for binding
// and also allow them to be declared in interfaces as function return type
UCLASS()
class BOTTERY_API UPolarityDelegateWrapper : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnPolarityChangedSignature OnPolarityChanged;
};
