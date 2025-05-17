// Fill out your copyright notice in the Description page of Project Settings.


#include "BotteryHUD.h"
#include "BotteryGameState.h"
#include "Blueprint/UserWidget.h"

void ABotteryHUD::BeginPlay()
{
    Super::BeginPlay();
    
    ShowUI("HUD");

    // Show game over UI on game over
    if (ABotteryGameState* GameState = Cast<ABotteryGameState>(GetWorld()->GetGameState()))
    {
        GameState->OnGameOver.AddUniqueDynamic(this, &ABotteryHUD::ShowGameOverUI);
    }

    /*for (auto& Pair : WidgetClasses)
    {
        if (Pair.Value)
        {
            UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), Pair.Value);
            if (Widget)
            {
                Widget->AddToViewport();
                Widget->SetVisibility(ESlateVisibility::Hidden);
                WidgetInstances.Add(Pair.Key, Widget);
            }
        }
    }

    if (WidgetInstances.Contains("HUD"))
    {
        ShowUI("HUD");
    }*/
}

void ABotteryHUD::ShowUI(FName WidgetKey)
{
    UUserWidget* Widget = WidgetInstances.FindRef(WidgetKey);
    if (Widget)
    {
        Widget->SetVisibility(ESlateVisibility::Visible);
    }
    else if (WidgetClasses.Contains(WidgetKey))
    {
        TSubclassOf<UUserWidget> Class = WidgetClasses[WidgetKey];
        if (Class)
        {
            UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), Class);
            if (NewWidget)
            {
                NewWidget->AddToViewport();
                WidgetInstances.Add(WidgetKey, NewWidget);
            }
        }
    }
}

void ABotteryHUD::HideUI(FName WidgetKey)
{
    UUserWidget* Widget = WidgetInstances.FindRef(WidgetKey);
    if (Widget)
    {
        Widget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ABotteryHUD::ShowGameOverUI(int32 Score)
{
    ShowUI("GameOver");
}
