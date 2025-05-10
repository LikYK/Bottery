// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UStatComponent::HasStat(EStatKey Key)
{
	return Stats.Contains(Key);
}

float UStatComponent::GetStatBase(EStatKey Key)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->GetBaseValue();
	}
	UE_LOG(LogTemp, Warning, TEXT("GetStatBase failed: stat is not valid."));
	return 0.0f;
}

float UStatComponent::GetStatMax(EStatKey Key)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->GetMaxValue();
	}
	UE_LOG(LogTemp, Warning, TEXT("GetStatMax failed: stat is not valid."));
	return 0.0f;
}

float UStatComponent::GetStatMin(EStatKey Key)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->GetMinValue();
	}
	UE_LOG(LogTemp, Warning, TEXT("GetStatMin failed: stat is not valid."));
	return 0.0f;
}

float UStatComponent::GetStatValue(EStatKey Key)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->GetValue();
	}
	UE_LOG(LogTemp, Warning, TEXT("GetStatValue failed: stat is not valid."));
	return 0.0f;
}

void UStatComponent::SetStatValue(EStatKey Key, float NewValue)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->SetValue(NewValue);
	}
	UE_LOG(LogTemp, Warning, TEXT("SetStatValue failed: stat is not valid."));
}

void UStatComponent::ModifyStat(EStatKey Key, float ChangeAmount)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->ModifyValue(ChangeAmount);
	}
	UE_LOG(LogTemp, Warning, TEXT("ModifyStat failed: stat is not valid."));
}

UStatDelegateWrapper* UStatComponent::GetStatDelegateWrapper(EStatKey Key)
{
	if (UStat* Stat = Stats.FindRef(Key))
	{
		return Stat->StatDelegateWrapper;
	}
	UE_LOG(LogTemp, Warning, TEXT("GetStatDelegateWrapper failed: stat is not valid."));
	return nullptr;
}

//UStat* UStatComponent::GetStat(EStatKey StatKey)
//{
//	UStat* Stat = nullptr;
//
//	// Use Find instead of FindRef because FindRef returns a default obj if not found
//	UStat** StatPtr = Stats.Find(StatKey);
//	if (StatPtr)
//	{
//		Stat = *StatPtr;
//	}
//
//	if (!Stat)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Get stat failed, stat not found."));
//	}
//
//	return Stat;
//}

