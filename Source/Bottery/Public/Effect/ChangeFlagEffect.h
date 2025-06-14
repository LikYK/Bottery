// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect.h"
#include "ActorData/Flag.h"
#include "ChangeFlagEffect.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UChangeFlagEffect : public UEffect
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect(AActor* Initiator, AActor* Target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Change Flag Effect")
	EFlagKey TargetFlag;
};
