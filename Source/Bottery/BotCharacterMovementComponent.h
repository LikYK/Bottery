// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BotCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UBotCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Speed")
	void UpdateSpeed(float NewSpeed, float BaseSpeed);

protected:
	virtual void BeginPlay() override;
};
