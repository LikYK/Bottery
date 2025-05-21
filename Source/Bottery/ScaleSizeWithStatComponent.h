// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stat.h"
#include "ScaleSizeWithStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOTTERY_API UScaleSizeWithStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScaleSizeWithStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Size Scaling")
	void UpdateScale(float NewTargetValue, float BaseTargetValue);

	UFUNCTION(BlueprintCallable, Category = "Size Scaling")
	float GetScale();

protected:
	UFUNCTION(BlueprintCallable, Category = "Size Scaling")
	void HandleTargetStatChange(float NewTargetValue, float BaseTargetValue);

	// The key of the stat to base the scale on
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Size Scaling")
	EStatKey TargetStatKey;

	// Cache of the stat to base the scale on
	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	UStat* TargetStat;

	// The component that will be scaled
	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	USceneComponent* TargetComponent;

	// Original scale of the TargetComponent
	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	FVector OriginalScale;

	// A local stat to store and manage the current scale
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Size Scaling")
	UStat* ScaleMultiplier;
};
