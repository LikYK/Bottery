// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Flag.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlagChangedSignature, bool, bCurrentValue);

UENUM(BlueprintType)
enum class EFlagKey : uint8
{
	Polarity    UMETA(DisplayName = "Polarity"),
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UFlag : public UObject
{
	GENERATED_BODY()
	
public:
	UFlag();

protected:
	virtual void PostInitProperties() override;
	//virtual void PostDuplicate(bool bDuplicateForPIE) override;
	virtual void PostLoad() override;

public:
	UFUNCTION(BlueprintCallable)
	bool GetBaseValue() const;

	UFUNCTION(BlueprintCallable)
	bool GetValue() const;

	UFUNCTION(BlueprintCallable)
	void SetValue(bool bNewValue);

	UFUNCTION(BlueprintCallable)
	void SwitchValue();

	UFUNCTION(BlueprintCallable)
	void RandomizeValue();

	UPROPERTY(BlueprintAssignable)
	FOnFlagChangedSignature OnFlagChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRandomBaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bRandomBaseValue", EditConditionHides))
	bool bBaseValue;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bValue;

private:
	void InitValue();
};
