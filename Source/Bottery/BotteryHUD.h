// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BotteryHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOTTERY_API ABotteryHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowUI(FName WidgetKey);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HideUI();

    //UFUNCTION(BlueprintCallable, Category = "UI")
    //void HideUI(FName WidgetKey);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void InitHUD();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowGameOverUI(int32 Score);

protected:
    UPROPERTY(EditAnywhere, Category = "UI")
    TMap<FName, TSubclassOf<UUserWidget>> WidgetClasses;

    UPROPERTY()
    TMap<FName, UUserWidget*> WidgetInstances; 

    // Only the top widget in the UIStack is visible
    TArray<FName> UIStack;
};
