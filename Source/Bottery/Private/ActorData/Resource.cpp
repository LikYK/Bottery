// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorData/Resource.h"

UResource::UResource()
{
    RegenRateStat = CreateDefaultSubobject<UStat>(TEXT("RegenRateStat"));
    DecayRateStat = CreateDefaultSubobject<UStat>(TEXT("DecayRateStat"));
}

void UResource::PostInitProperties()
{
    Super::PostInitProperties();

    // After properties are loaded from defaults, set current value = base value
    // This works when the UStat is added in C++ through CreateDefaultObject<>
    InitValue();
}

void UResource::PostLoad()
{
    Super::PostLoad();

    // Set current value = base value for instances added through blueprints/editor
    InitValue();
}

void UResource::Tick(float DeltaTime)
{
    if (bRegenerate)
    {
        ModifyValue(RegenRateStat->GetValue() * DeltaTime);
    }
    if (bDecay)
    {
        ModifyValue(-DecayRateStat->GetValue() * DeltaTime);
    }
}

bool UResource::IsTickable() const
{
    // Only tick when game is running
    if (UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::ReturnNull))
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

// Unreal requires an ID for a tickable object in order to profile its ticking performance
// RETURN_QUICK_DECLARE_CYCLE_STAT macro creates an ID for this class
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

void UResource::SetMaxValue(float NewMaxValue)
{
    MaxValue = NewMaxValue;
}

void UResource::SetValue(float NewValue)
{
    float OldValue = CurrentValue;
    CurrentValue = FMath::Clamp(NewValue, 0.0f, MaxValue);

    OnResourceChanged.Broadcast(CurrentValue, MaxValue, NewValue - OldValue);
    if (CurrentValue <= 0.0f && !bDepleted)
    {
        bDepleted = true;
        OnResourceDepleted.Broadcast();
    }
    if (CurrentValue > 0.0f && bDepleted)
    {
        bDepleted = false; // If is depleted and value restored to above 0.0f, set depleted back to false
    }
}

void UResource::ModifyValue(float ChangeAmount)
{
    SetValue(CurrentValue + ChangeAmount);
}

void UResource::SetRegenerate(bool bNewVal)
{
    bRegenerate = bNewVal;
}

void UResource::SetDecay(bool bNewVal)
{
    bDecay = bNewVal;
}

UStat* UResource::GetDecayRateStat()
{
    return DecayRateStat;
}

UStat* UResource::GetRegenRateStat()
{
    return RegenRateStat;
}

void UResource::InitValue()
{
    CurrentValue = MaxValue;
}
