// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "ChangeHealthEffect.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UChangeHealthEffect : public UEffect
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect(AActor* Initiator, AActor* Target) override;
};
