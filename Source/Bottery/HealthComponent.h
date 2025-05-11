// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthInterface.h"
#include "HealthDelegateWrapper.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Health), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UHealthComponent : public UActorComponent, public IHealthInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual float GetCurrentHealth_Implementation() override;

	virtual float GetMaxHealth_Implementation() override;

	virtual void TakeDamage_Implementation(float Damage) override;

	virtual UHealthDelegateWrapper* GetHealthDelegateWrapper_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	UHealthDelegateWrapper* HealthDelegateWrapper;
};
