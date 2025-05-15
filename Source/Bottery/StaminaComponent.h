// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, CurrentStamina, float, MaxStamina);

UCLASS()
class BOTTERY_API UStaminaDelegateWrapper : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnStaminaChangedSignature OnStaminaChanged;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetCurrentStamina();

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetMaxStamina();

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void UseStamina(float UseAmount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetRegenRate();

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetRegenRate(float NewRate);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void ModifyRegenRate(float RateChange);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	UStaminaDelegateWrapper* GetStaminaDelegateWrapper();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float RegenRate = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	UStaminaDelegateWrapper* StaminaDelegateWrapper;
};
