// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UEffect : public UObject
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Effect")
    virtual void ApplyEffect(AActor* Initiator, AActor* Target) PURE_VIRTUAL(&UEffect::ApplyEffect,);
};
