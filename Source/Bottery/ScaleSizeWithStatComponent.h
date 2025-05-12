// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatKey.h"
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
	void HandleTargetStatChange(float NewTargetValue, float BaseTargetValue);

	UFUNCTION(BlueprintCallable, Category = "Size Scaling")
	void UpdateScale(float NewTargetValue, float BaseTargetValue);

protected:
	// The stat to base the scale on
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Size Scaling")
	EStatKey TargetStat;

	// The somponent that will be scaled
	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	USceneComponent* TargetComponent;

	// Original scale of the TargetComponent
	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	FVector OriginalScale;

	// Stored here because this stat is used only in this component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Size Scaling")
	UStat* ScaleMultiplier;

	// Cache TargetStat's minimum and maximum for ScaleMultiplier's calculation
	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	float TargetMin;

	UPROPERTY(BlueprintReadOnly, Category = "Size Scaling")
	float TargetMax;
};
