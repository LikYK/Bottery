// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatKey.generated.h"

UENUM(BlueprintType)
enum class EStatKey : uint8
{
    Magnitude    UMETA(DisplayName = "Magnitude"),
    Speed     UMETA(DisplayName = "Speed"),
};
