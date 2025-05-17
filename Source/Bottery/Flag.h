// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlagDelegateWrapper.h"
#include "Flag.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UFlag : public UObject
{
	GENERATED_BODY()
	
public:
	UFlag();

protected:
	virtual void PostInitProperties() override;
	virtual void PostDuplicate(bool bDuplicateForPIE) override;

public:
	UFUNCTION(BlueprintCallable)
	bool GetBaseValue();

	UFUNCTION(BlueprintCallable)
	bool GetValue();

	UFUNCTION(BlueprintCallable)
	void SetValue(bool bNewValue);

	UFUNCTION(BlueprintCallable)
	void SwitchValue();

	UFUNCTION(BlueprintCallable)
	void RandomizeValue();

	UPROPERTY(BlueprintReadOnly)
	UFlagDelegateWrapper* DelegateWrapper;

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
