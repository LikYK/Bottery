// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangedSignature, int, CurrentHealth, int, MaxHealth, float, Fill);

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
	int32 GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthBarFill();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(int32 Damage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth = 0;
};
