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

    UFUNCTION(BlueprintCallable, Category = "SaveLoad")
    void SaveProgress(float NewScore);

    UFUNCTION(BlueprintPure, Category = "HighScore")
    float GetHighScore() const { return HighScore; }

    UFUNCTION(BlueprintPure, Category = "MaxHealth")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintPure, Category = "FirstLaunch")
    bool IsFirstLaunch() const { return bIsFirstLaunch; }

protected:
    UPROPERTY(VisibleAnywhere, Category = "HighScore")
    float HighScore = 0;

    UPROPERTY(VisibleAnywhere, Category = "MaxHealth")
    float MaxHealth = 100;

    UPROPERTY(VisibleAnywhere, Category = "FirstLaunch")
    bool bIsFirstLaunch;

    UPROPERTY(EditAnywhere, Category = "SaveLoad")
    FString SaveSlotName = TEXT("DefaultSaveSlot");

    UPROPERTY(EditAnywhere, Category = "SaveLoad")
    uint32 UserIndex = 0;
};
