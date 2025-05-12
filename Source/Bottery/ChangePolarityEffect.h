// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "ChangePolarityEffect.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UChangePolarityEffect : public UEffect
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect(AActor* Initiator, AActor* Target) override;
};
