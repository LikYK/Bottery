// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerEffectComponent.h"
#include "HasHealth.h"
#include "TriggerChangeHealthComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Effects), meta = (BlueprintSpawnableComponent))
class BOTTERY_API UTriggerChangeHealthComponent : public UTriggerEffectComponent
{
	GENERATED_BODY()
	
protected:
	virtual void ApplyEffect(AActor* Target, float EffectMagnitude) override;
};
