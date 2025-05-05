// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.h"
#include "HealthGrowthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UHealthGrowthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthGrowthComponent();

	UFUNCTION(BlueprintCallable, Category = "HealthGrowth")
	int32 GetGrowthRate();

	UFUNCTION(BlueprintCallable, Category = "HealthGrowth")
	void SetGrowthRate(int32 NewRate);

	UFUNCTION(BlueprintCallable, Category = "HealthGrowth")
	void ChangeGrowthRate(int32 RateChange);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "HealthGrowth")
	void ApplyGrowthRate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthGrowth")
	int32 GrowthRate = 0;

	UPROPERTY()
	UHealthComponent* HealthComponent;

	FTimerHandle ApplyTimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
