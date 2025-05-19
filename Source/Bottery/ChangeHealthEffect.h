// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "ChangeHealthEffect.generated.h"

/**
 * This effect heals the target(character) when the it and the initiator(orb) have same polarity, otherwise it damages the target
 */
UCLASS()
class BOTTERY_API UChangeHealthEffect : public UEffect
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect(AActor* Initiator, AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HealSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DamageSound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	//USoundAttenuation* EffectSoundAttenuation;
};
