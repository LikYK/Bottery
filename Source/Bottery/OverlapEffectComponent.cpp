// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapEffectComponent.h"

// Sets default values for this component's properties
UOverlapEffectComponent::UOverlapEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOverlapEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	if (auto* Primitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
	{
		Primitive->OnComponentBeginOverlap.AddUniqueDynamic(this, &UOverlapEffectComponent::HandleOverlap);
	}
}

void UOverlapEffectComponent::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("overlap handler")));
	//if (!EffectInstance)
	//{
	//	CreateEffectInstance();
	//}

	Effect->ApplyEffect(GetOwner(), OtherActor);
	//if (GEngine)GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Overlap destroy")));
	GetOwner()->Destroy();
}

