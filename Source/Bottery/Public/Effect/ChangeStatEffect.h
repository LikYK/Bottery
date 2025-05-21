// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "ActorData/Stat.h"
#include "ChangeStatEffect.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UChangeStatEffect : public UEffect
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect(AActor* Initiator, AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Change Stat Effect")
	EStatKey TargetStat;
};
