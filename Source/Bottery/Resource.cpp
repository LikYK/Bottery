// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"

UResource::UResource()
{
    RegenRateStat = CreateDefaultSubobject<UStat>(TEXT("RegenRateStat"));
}

void UResource::PostInitProperties()
{
    Super::PostInitProperties();

    InitValue();
}

void UResource::PostLoad()
{
    Super::PostLoad();

    InitValue();
}

//void UResource::PostDuplicate(bool bDuplicateForPIE)
//{
//    Super::PostDuplicate(bDuplicateForPIE);
//
//    InitValue();
//}

void UResource::Tick(float DeltaTime)
{
    //if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ResourceTick, bRegen:%d, delta:%f, regenval:%f"), bRegenerate, DeltaTime, RegenRateStat->GetValue()));
    //UE_LOG(LogTemp, Warning, TEXT("ResourceTick"));
    if (bRegenerate)
    {
        ModifyValue(RegenRateStat->GetValue() * DeltaTime);
    }
}

bool UResource::IsTickable() const
{
    // Only tick when game is running
    if (UWorld* World = GetWorld())
    {
        return World->IsGameWorld();
    }
    return false;
}

ETickableTickType UResource::GetTickableTickType() const
{
    return ETickableTickType::Conditional;
}

bool UResource::IsTickableInEditor() const
{
    return false;
}

bool UResource::IsTickableWhenPaused() const
{
    return false;
}

UWorld* UResource::GetTickableGameObjectWorld() const
{
    return GetWorld();
}

TStatId UResource::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UResource, STATGROUP_Tickables);
}

float UResource::GetValue() const
{
    return CurrentValue;
}

float UResource::GetMaxValue() const
{
    return MaxValue;
}

void UResource::SetValue(float NewValue)
{
    float OldValue = CurrentValue;
    CurrentValue = FMath::Clamp(NewValue, 0.0f, MaxValue);
    OnResourceChanged.Broadcast(CurrentValue, MaxValue, NewValue - OldValue);
}

void UResource::ModifyValue(float ChangeAmount)
{
    SetValue(CurrentValue + ChangeAmount);
}

UStat* UResource::GetRegenRateStat()
{
    return RegenRateStat;
}

void UResource::InitValue()
{
    SetValue(MaxValue);
}
