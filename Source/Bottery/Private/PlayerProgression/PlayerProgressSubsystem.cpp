// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProgression/PlayerProgressSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerProgression/BotterySaveGame.h"

void UPlayerProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        if (UBotterySaveGame* Loaded = Cast<UBotterySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)))
        {
            HighScore = Loaded->HighScore;
            MaxHealth = Loaded->MaxHealth;
            //if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Load successful, highscore: %f, maxhealth: %f"), HighScore, MaxHealth));
        }
        else 
        {
            //if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Load failed, cast failed")));
        }
    }
    else 
    {
        //if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Load failed, no save exists")));
    }
}

void UPlayerProgressSubsystem::SaveProgress(float NewScore)
{
    // Save progress if a new high score is achieved or max health increment is eligible (+1 per 100 score)
    if (NewScore > HighScore || NewScore >= 100.0f)
    {
        if (NewScore > HighScore)
        {
            HighScore = NewScore;
        }
        
        if (NewScore >= 100.0f)
        {
            int32 HealthAddAmount = NewScore / 100;
            MaxHealth += HealthAddAmount;
        }

        UBotterySaveGame* ToSave = Cast<UBotterySaveGame>(UGameplayStatics::CreateSaveGameObject(UBotterySaveGame::StaticClass()));
        ToSave->HighScore = HighScore;
        ToSave->MaxHealth = MaxHealth;
        UGameplayStatics::SaveGameToSlot(ToSave, SaveSlotName, UserIndex);
        //if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Save successful, new highscore:%f, new health:%f"), HighScore, MaxHealth));
    }
}
