// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Polarity.generated.h"

UENUM(BlueprintType)
enum class EPolarity : uint8
{
	Negative UMETA(DisplayName = "Negative"),
	Positive UMETA(DisplayName = "Positive"),
};
