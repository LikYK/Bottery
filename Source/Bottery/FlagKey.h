// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlagKey.generated.h"

UENUM(BlueprintType)
enum class EFlagKey : uint8
{
    Polarity    UMETA(DisplayName = "Polarity"),
};
