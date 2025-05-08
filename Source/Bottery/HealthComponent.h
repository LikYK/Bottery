// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthDelegateWrapper.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Health), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UHealthComponent : public UActorComponent
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
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthDelegateWrapper* HealthDelegateWrapper;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;
};
