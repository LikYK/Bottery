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
    // Show widget that corresponds to the WidgetKey
    UUserWidget* Widget = WidgetInstances.FindRef(WidgetKey);
    if (Widget)
    {
        Widget->SetVisibility(ESlateVisibility::Visible);
    }
    else if (WidgetClasses.Contains(WidgetKey))
    {
        TSubclassOf<UUserWidget> Class = WidgetClasses[WidgetKey];
        Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), Class);
        if (Widget)
        {
            Widget->AddToViewport();
            WidgetInstances.Add(WidgetKey, Widget);
        }
    }

    // Other widget exists in the UIStack, hide the top widget first then add this widget to the stack
    if (UIStack.Num() > 0) 
    {
        FName TopKey = UIStack.Last();
        if (UUserWidget* TopWidget = WidgetInstances.FindRef(TopKey))
        {
            TopWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    UIStack.Push(WidgetKey);

    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

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

//void ABotteryHUD::HideUI(FName WidgetKey)
//{
//    UUserWidget* Widget = WidgetInstances.FindRef(WidgetKey);
//    if (Widget)
//    {
//        Widget->SetVisibility(ESlateVisibility::Hidden);
//    }
//}

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

void ABotteryHUD::ShowGameOverUI(int32 Score)
{
    ShowUI("GameOver");
}
