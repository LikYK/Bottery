// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProgressSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "BotterySaveGame.h"

void UPlayerProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        if (UBotterySaveGame* Loaded = Cast<UBotterySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)))
        {
            HighScore = Loaded->HighScore;
            if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Load successful, highscore: %f"), HighScore));
            UE_LOG(LogTemp, Warning, TEXT("Load successful, highscore: %f"), HighScore);
        }
        else 
        {
            if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Load failed, cast failed")));
            UE_LOG(LogTemp, Warning, TEXT("Load failed, cast failed"));
        }
    }
    else {
        if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Load failed, no save exists")));
        UE_LOG(LogTemp, Warning, TEXT("Load failed, no save exists"));
    }
}

void UPlayerProgressSubsystem::SaveProgress(float NewScore)
{
    if (NewScore > HighScore)
    {
        HighScore = NewScore;

        UBotterySaveGame* ToSave = Cast<UBotterySaveGame>(UGameplayStatics::CreateSaveGameObject(UBotterySaveGame::StaticClass()));
        ToSave->HighScore = HighScore;
        UGameplayStatics::SaveGameToSlot(ToSave, SaveSlotName, UserIndex);
        if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Save successful, new highscore:%f"), HighScore));
        UE_LOG(LogTemp, Warning, TEXT("Save successful, new highscore:%f"), HighScore);
    }
    else {
        if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Save failed, not highscore, current score:%f, highscore:%f"),NewScore, HighScore));
        UE_LOG(LogTemp, Warning, TEXT("Save failed, not highscore, current score:%f, highscore:%f"), NewScore, HighScore);
    }
}
