// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceDelegateWrapper.h"
#include "Stat.h"
#include "Resource.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class BOTTERY_API UResource : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UResource();

protected:
	virtual void PostInitProperties() override;
	//virtual void PostDuplicate(bool bDuplicateForPIE) override;
	virtual void PostLoad() override;

public:
	// Override FTickableGameObject interface functions, to make this UObject tickable
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickableInEditor() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	float GetValue() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	float GetMaxValue() const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void SetValue(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void ModifyValue(float ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	UStat* GetRegenRateStat();

	UPROPERTY(BlueprintReadOnly, Category = "Resource")
	UResourceDelegateWrapper* DelegateWrapper;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	float MaxValue = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Resource")
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	bool bRegenerate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Resource")
	UStat* RegenRateStat;

private:
	void InitValue();
};
