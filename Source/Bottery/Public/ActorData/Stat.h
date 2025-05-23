// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Stat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChangedSignature, float, CurrentValue, float, BaseValue);

UENUM(BlueprintType)
enum class EStatKey : uint8
{
	Magnitude    UMETA(DisplayName = "Magnitude"),
	Speed     UMETA(DisplayName = "Speed"),
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UStat : public UObject
{
	GENERATED_BODY()
	
public:
	UStat();

protected:
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetBaseValue() const;

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetMaxValue() const;

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetMinValue() const;

	UFUNCTION(BlueprintCallable, Category = "Stat")
	float GetValue() const;

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SetValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void ModifyValue(float ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void InitValue();

	UPROPERTY(BlueprintAssignable, Category = "Stat")
	FOnStatChangedSignature OnStatChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	bool bRandomInitialValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MinValue;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stat")
	float Value;
};
