// Fill out your copyright notice in the Description page of Project Settings.


#include "BotteryHUD.h"
#include "BotteryGameState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABotteryHUD::BeginPlay()
{
    Super::BeginPlay();
    
    InitHUD();

    // Show game over UI on game over
    if (ABotteryGameState* GameState = Cast<ABotteryGameState>(GetWorld()->GetGameState()))
    {
        GameState->OnGameOver.AddUniqueDynamic(this, &ABotteryHUD::ShowGameOverUI);
    }
}

// Show HUD widget, HUD is not added into the UIStack
void ABotteryHUD::InitHUD()
{
    if (WidgetClasses.Contains("HUD"))
    {
        TSubclassOf<UUserWidget> Class = WidgetClasses["HUD"];
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), Class);
        if (Widget)
        {
            Widget->AddToViewport();
            WidgetInstances.Add("HUD", Widget);
        }
    }
}

// Show UI/widget that corresponds to the WidgetKey
void ABotteryHUD::ShowUI(FName WidgetKey)
{
    // If other UI/widget exists in the UIStack, hide the top widget
    if (UIStack.Num() > 0)
    {
        FName TopKey = UIStack.Last();
        if (UUserWidget* TopWidget = WidgetInstances.FindRef(TopKey))
        {
            TopWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    UUserWidget* Widget = WidgetInstances.FindRef(WidgetKey);
    if (Widget)
    {
        // If widget instance is already created, toggle its visibility to show
        Widget->SetVisibility(ESlateVisibility::Visible);
    }
    else if (WidgetClasses.Contains(WidgetKey))
    {
        // Else create an instance from the corresponding class and add to viewport
        TSubclassOf<UUserWidget> Class = WidgetClasses[WidgetKey];
        Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), Class);
        if (Widget)
        {
            Widget->AddToViewport();
            WidgetInstances.Add(WidgetKey, Widget);
        }
    }

    // Push the newly added/shown widget to the stack and pause game
    UIStack.Push(WidgetKey);
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

// Hides the top-most UI currently shown
void ABotteryHUD::HideUI()
{
    if (UIStack.Num() == 0)
    {
        return;
    }
    
    FName TopKey = UIStack.Pop();
    if (UUserWidget* TopWidget = WidgetInstances.FindRef(TopKey))
    {
        TopWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (UIStack.Num() == 0)
    {
        // If no more item in stack, resume game
        UGameplayStatics::SetGamePaused(GetWorld(), false);
    }
    else
    {
        // Else show the new top widget
        FName NextKey = UIStack.Last();
        if (UUserWidget* NextWidget = WidgetInstances.FindRef(NextKey))
        {
            NextWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }

}

void ABotteryHUD::ShowGameOverUI(float Score)
{
    ShowUI("GameOver");
}

// Handles ESC key input
void ABotteryHUD::HandlePauseAction()
{
    if (UIStack.Num() == 0)
    {
        ShowUI("Pause");
    }
    else
    {
        HideUI();
    }
}
