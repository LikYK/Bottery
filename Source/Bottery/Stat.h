// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatDelegateWrapper.h"
#include "Stat.generated.h"

//DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnStatChangedSignature, float, CurrentValue, float, BaseValue);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChangedSignature, float, CurrentValue, float, BaseValue);

// An object that stores a base stat and applies a multiplier to it
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UStat : public UObject
{
	GENERATED_BODY()
	
public:
	UStat();

protected:
	virtual void PostInitProperties() override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetBaseValue();

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetMaxValue();

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetMinValue();

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetValue();

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void ModifyValue(float ChangeAmount);

	UPROPERTY(BlueprintReadOnly, Category = "Stat")
	UStatDelegateWrapper* DelegateWrapper;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MinValue;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stat")
	float Value;
};
