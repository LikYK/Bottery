// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Orb.h"
#include "HasStats.h"
#include "StatComponent.h"
#include "HasPolarity.h"
#include "PolarityComponent.h"
#include "SpeedOrb.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API ASpeedOrb : public AOrb, public IHasStats, public IHasPolarity
{
	GENERATED_BODY()
	
public:
	ASpeedOrb();

	virtual bool HasStat_Implementation(EStatKey Key) override;

	virtual float GetStatBase_Implementation(EStatKey Key) override;

	virtual float GetStatMax_Implementation(EStatKey Key) override;

	virtual float GetStatMin_Implementation(EStatKey Key) override;

	virtual float GetStatValue_Implementation(EStatKey Key) override;

	virtual void SetStatValue_Implementation(EStatKey Key, float NewValue) override;

	virtual void ModifyStat_Implementation(EStatKey Key, float ChangeAmount) override;

	virtual UStatDelegateWrapper* GetStatDelegateWrapper_Implementation(EStatKey Key) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	UStatComponent* StatComponent;

public:
	virtual EPolarity GetPolarity_Implementation() override;

	virtual void SetPolarity_Implementation(EPolarity NewPolarity) override;

	virtual void SwitchPolarity_Implementation() override;

	virtual FLinearColor GetPolarityColour_Implementation() override;

	virtual UPolarityDelegateWrapper* GetPolarityDelegateWrapper_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Polarity")
	UPolarityComponent* PolarityComponent;
};
