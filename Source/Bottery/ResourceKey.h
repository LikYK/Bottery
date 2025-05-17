// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceKey.generated.h"

UENUM(BlueprintType)
enum class EResourceKey : uint8
{
    Health UMETA(DisplayName = "Health"),
    Stamina UMETA(DisplayName = "Stamina"),
};
