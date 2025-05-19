// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerProgressSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API UPlayerProgressSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Saves high score on game over.
    UFUNCTION(BlueprintCallable, Category = Basic)
    void SaveProgress(float NewScore);

    UFUNCTION(BlueprintPure, Category = Basic)
    float GetHighScore() const { return HighScore; }

    UFUNCTION(BlueprintPure, Category = Basic)
    float GetMaxHealth() const { return MaxHealth; }

protected:
    UPROPERTY(VisibleAnywhere, Category = Basic)
    float HighScore = 0;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    float MaxHealth = 100;

    UPROPERTY(EditAnywhere, Category = Basic)
    FString SaveSlotName = TEXT("DefaultSaveSlot");

    UPROPERTY(EditAnywhere, Category = Basic)
    uint32 UserIndex = 0;
};
