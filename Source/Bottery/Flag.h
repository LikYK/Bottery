// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Flag.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlagChangedSignature, bool, bCurrentValue);

UENUM(BlueprintType)
enum class EFlagKey : uint8
{
	Polarity UMETA(DisplayName = "Polarity"),
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UFlag : public UObject
{
	GENERATED_BODY()
	
public:
	UFlag();

protected:
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Flag")
	bool GetBaseValue() const;

	UFUNCTION(BlueprintCallable, Category = "Flag")
	bool GetValue() const;

	UFUNCTION(BlueprintCallable, Category = "Flag")
	void SetValue(bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = "Flag")
	void SwitchValue();

	UFUNCTION(BlueprintCallable, Category = "Flag")
	void RandomizeValue();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void InitValue();

	UPROPERTY(BlueprintAssignable, Category = "Flag")
	FOnFlagChangedSignature OnFlagChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
	bool bRandomBaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag", meta = (EditCondition = "!bRandomBaseValue", EditConditionHides))
	bool bBaseValue;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Flag")
	bool bValue;
};
