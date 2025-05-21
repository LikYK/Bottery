// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "OrbMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UOrbMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Speed")
	void Init();

	UFUNCTION(BlueprintCallable, Category = "Speed")
	void UpdateSpeed(float NewSpeed, float BaseSpeed);

protected:
	virtual void BeginPlay() override;
};
