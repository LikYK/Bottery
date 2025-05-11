// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "ChangeSpeedEffect.generated.h"

/**
 * 
 */
UCLASS(meta = (RequiresPolarity = "true", RequiresMagnitude = "true"))
class BOTTERY_API UChangeSpeedEffect : public UEffect
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect(AActor* Initiator, AActor* Target) override;
};
