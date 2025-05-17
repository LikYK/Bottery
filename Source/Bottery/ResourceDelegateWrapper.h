// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceDelegateWrapper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResourceChangedSignature, float, CurrentValue, float, MaxValue, float, ChangeAmount);

// This is a wrapper class that contains delegates related to resources
// Wrapping delegates allow them to be passed to blueprints for binding
// and also allow them to be declared in interfaces as function return type
UCLASS()
class BOTTERY_API UResourceDelegateWrapper : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnResourceChangedSignature OnResourceChanged;
};
